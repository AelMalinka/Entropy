/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Socket.hh"

#include <algorithm>
#include <boost/asio/read.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/asio/write.hpp>

using namespace Entropy::Net;
using namespace Entropy::Net::asio;

using std::size_t;
using std::string;
using std::shared_ptr;
using std::lock_guard;
using std::mutex;
using std::move;
using std::make_shared;
using std::copy_n;

using std::cout;
using std::endl;

using boost::system::error_code;

Socket::Socket(Application &app)
	: _app(app), _sock(app.Io())
{}

Socket::~Socket() = default;

struct read_closure
{
	read_closure(Socket &, Application &, streambuf &, const shared_ptr<lock_guard<mutex>> &, const size_t);
	read_closure(Socket &, Application &, streambuf &, const shared_ptr<lock_guard<mutex>> &, const string &);
	void operator () (const error_code &, const size_t);
	private:
		Socket &_sock;
		Application &_app;
		streambuf &_buff;
		shared_ptr<lock_guard<mutex>> _lock;
		size_t _len;
		string _delim;
};

void Socket::Write(string &&msg)
{
	size_t len = msg.size();
	async_write(socket(), buffer(move(msg)), [this, len](const error_code &ec, size_t bytes) {
		if(bytes != len)
			_app.onError(ENTROPY_ATTACH_TRACE(IncompleteTransfer("Write")) << BytesTransfered(bytes) << BytesExpected(len));
		if(ec)
			_app.onError(ENTROPY_ATTACH_TRACE(Exception("Write Error")) << SystemError(ec));
	});
}

void Socket::Read(const size_t &len)
{
	// 2014-01-13 AMR NOTE: keep lock_guard alive and active until closure destructs 
	// 2014-01-13 AMR NOTE: wants c++14 NAO!!!
	auto l = make_shared<lock_guard<mutex>>(_read_lock);
	read_closure c(*this, _app, _read_buff, l, len);
	async_read(socket(), _read_buff, c);
}

void Socket::Read(const string &delim)
{
	// 2014-01-13 AMR NOTE: keep lock_guard alive and active until closure destructs 
	// 2014-01-13 AMR NOTE: wants c++14 NAO!!!
	auto l = make_shared<lock_guard<mutex>>(_read_lock);
	read_closure c(*this, _app, _read_buff, l, delim);
	async_read_until(socket(), _read_buff, delim, c);
}
#include<iostream>
void Socket::Cancel()
{
	cout << "canceling" << endl;
	socket().cancel();
}

void read_closure::operator () (const error_code &ec, const size_t bytes)
{
	if(ec)
		_app.onError(ENTROPY_ATTACH_TRACE(Exception("Read Failed")) << SystemError(ec));
	else if(_len != 0 && bytes != _len)
		_app.onError(ENTROPY_ATTACH_TRACE(IncompleteTransfer("Read")) << BytesTransfered(bytes) << BytesExpected(_len));
	else
	{
		// 2014-01-13 AMR HACK: is very bad TODO
		const char *ptr = asio::buffer_cast<const char *>(*_buff.data().begin());
		string data(ptr, bytes);
		if(_delim != "" && data.rfind(_delim) == string::npos)
			_app.onError(ENTROPY_ATTACH_TRACE(IncompleteTransfer("Read")) << StringTransfered(data) << StringExpected(_delim));
		else
		{
			_buff.consume(bytes);
			_lock.reset();
			_app.onData(_sock, move(data));
		}
	}
}

read_closure::read_closure(Socket &sock, Application &app, streambuf &buff, const shared_ptr<lock_guard<mutex>> &l, const size_t len)
	: _sock(sock), _app(app), _buff(buff), _lock(l), _len(len), _delim("")
{}

read_closure::read_closure(Socket &sock, Application &app, streambuf &buff, const shared_ptr<lock_guard<mutex>> &l, const string &delim)
	: _sock(sock), _app(app), _buff(buff), _lock(l), _len(0), _delim(delim)
{}

Entropy::Net::asio::ip::tcp::socket &Socket::socket()
{
	return _sock;
}

Application &Socket::application()
{
	return _app;
}
