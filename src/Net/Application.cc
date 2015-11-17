/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "Application.hh"

using namespace Entropy::Net;
using namespace std;

Application::Application() = default;
Application::~Application() = default;

void Application::onError(const Net::Exception &e)
{
	throw e;
}

asio::io_service &Application::Io()
{
	return _io;
}
