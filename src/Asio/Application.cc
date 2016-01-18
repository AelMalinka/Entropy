/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Application.hh"

using namespace Entropy::Asio;

Application::Application(Asio::Loop &l)
	: Entropy::Application(), _loop(l)
{}

Application::Application(Asio::Loop &l, int ArgC, char *ArgV[])
	: Entropy::Application(ArgC, ArgV), _loop(l)
{}

Application::~Application() = default;

void Application::operator () ()
{
	_loop();
}

Entropy::Asio::Loop &Application::Loop()
{
	return _loop;
}
