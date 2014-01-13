/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <cstring>
#include <iostream>

#include "Client.hh"
#include "Server.hh"
#include "Protocols/Line.hh"

using namespace Entropy;
using namespace std;

struct Application :
	public Net::Protocols::Line
{
	Application(const bool);
	bool onMessage(Net::Socket &, string &&);
	void onConnect(Net::Socket &);
	void onError(const Net::Exception &);
	private:
		bool _clientserver;
		unique_ptr<Net::Client> _client;
		unique_ptr<Net::Server> _server;
};

int main(int argc, char *argv[])
{
	if(argc != 2)
		return EXIT_FAILURE;

	try
	{
		if(strcmp(argv[1], "--client") == 0)
		{
			Application app(true);
			app.Io().run();
		}
		else if(strcmp(argv[1], "--server") == 0)
		{
			Application app(false);
			app.Io().run();
		}
		else
			return EXIT_FAILURE;

		return EXIT_SUCCESS;
	}
	catch(Net::Exception &e)
	{
		cout << e << endl;
		if(e.has<Net::SystemError>())
			cout << e.get<Net::SystemError>().message() << endl;
		return EXIT_FAILURE;
	}
	catch(Net::Shutdown)
	{
		return EXIT_SUCCESS;
	}
	catch(exception &e)
	{
		cout << e << endl;
		return EXIT_FAILURE;
	}
};

::Application::Application(const bool client)
	: _clientserver(client)
{
	if(_clientserver)
		_client = unique_ptr<Net::Client>(new Net::Client(*this, "localhost:14242"));
	else
		_server = unique_ptr<Net::Server>(new Net::Server(*this, "localhost", "14242"));
}

void ::Application::onConnect(Net::Socket &sock)
{
	Net::Protocols::Line::onConnect(sock);
	cout << "Connected" << endl;

	if(_clientserver)
		sock.Write("Hello!\n");
}

bool ::Application::onMessage(Net::Socket &s, string &&msg)
{
	cout << msg << endl;

	if(!_clientserver)
		s.Write(move(msg + "\n"));
	else
		return false;

	return true;
}

void ::Application::onError(const Net::Exception &e)
{
	if(e.has<Net::SystemError>() && e.get<Net::SystemError>() == Net::asio::error::misc_errors::eof)
		throw Net::Shutdown();
	else
		Net::Application::onError(e);
}
