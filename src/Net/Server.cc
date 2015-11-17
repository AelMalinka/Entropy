/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "Server.hh"

#include <functional>

using namespace Entropy::Net;
using namespace std;

Server::Server(Application &app, const string &hostport)
	: _app(app), _sockets(), _acceptor(_app.Io()), _work(_app.Io())
{
	string host, port;
	host = hostport.substr(0, hostport.rfind(":"));
	port = hostport.substr(hostport.rfind(":") + 1);
	listen(host, port);
}

Server::Server(Application &app, const string &host, const string &port)
	: _app(app), _sockets(), _acceptor(_app.Io()), _work(_app.Io())
{
	listen(host, port);
}

Server::~Server() = default;

namespace Entropy { namespace Net { namespace detail {
	function<void()> connect;
}}}

void Server::listen(const string &host, const string &port)
{
	using Entropy::Net::asio::ip::tcp;
	using boost::system::error_code;

	// 2014-01-13 AMR NOTE: []() by reference requires objects to survive, tcp::resolvers can't be copied
	auto res = make_shared<tcp::resolver>(_app.Io());
	tcp::resolver::query q(host, port);

	res->async_resolve(q, [this, res, q](const error_code &ec, tcp::resolver::iterator i) {
		if(ec) {
			_app.onError(ENTROPY_ATTACH_TRACE(Exception("Resolve Failed")) << SystemError(ec));
		} else {
			_acceptor.open(i->endpoint().protocol());
			_acceptor.set_option(asio::socket_base::reuse_address(true));
			_acceptor.bind(i->endpoint());
			// 2014-01-11 AMR TODO: listen backlog
			_acceptor.listen();

			detail::connect = [this]() {
				list<Socket>::iterator sock;
				{
					lock_guard<mutex> g(_mutex);
					sock = _sockets.emplace(_sockets.end(), _app);
				}
				_acceptor.async_accept(sock->socket(), [this, sock](const error_code &ec) {
					if(ec) {
						lock_guard<mutex> g(_mutex);
						_sockets.erase(sock);
						_app.onError(ENTROPY_ATTACH_TRACE(Exception("Listen Failed")) << SystemError(ec));
					} else {
						_app.onConnect(*sock);
					}
					detail::connect();
				});
			};
			detail::connect();
		}
	});
}
