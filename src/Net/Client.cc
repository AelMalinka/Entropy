/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Client.hh"

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace Entropy::Net;
using namespace std;

Client::Client(Application &app, const string &hostport)
	: Socket(app)
{
	string host, port;
	host = hostport.substr(0, hostport.rfind(":"));
	port = hostport.substr(hostport.rfind(":") + 1);
	connect(host, port);
}

Client::Client(Application &app, const string &host, const string &port)
	: Socket(app)
{
	connect(host, port);
}

Client::~Client() = default;

void Client::connect(const string &host, const string &port)
{
	using Entropy::Net::asio::ip::tcp;
	using boost::system::error_code;

	// 2014-01-13 AMR NOTE: []() by reference requires objects to survive, tcp::resolvers can't be copied
	auto res = make_shared<asio::ip::tcp::resolver>(application().Io());
	asio::ip::tcp::resolver::query q(host, port);

	res->async_resolve(q, [this, res, q](const error_code &ec, tcp::resolver::iterator i) {
		if(ec) {
			application().onError(ENTROPY_ATTACH_TRACE(Exception("Resolve Failed")) << SystemError(ec));
		} else {
			async_connect(socket(), i, [this](const error_code &ec, tcp::resolver::iterator) {
				if(ec) {
					application().onError(ENTROPY_ATTACH_TRACE(Exception("Connect Failed")) << SystemError(ec));
				} else {
					application().onConnect(*this);
				}
			});
		}
	});
}
