/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Application.hh"

using namespace Entropy::Asio;

Application::Application()
	: Entropy::Application()
{}

Application::Application(int ArgC, char *ArgV[])
	: Entropy::Application(ArgC, ArgV)
{}

Application::~Application() = default;

void Application::operator () ()
{
	_loop();
}

UV::Loop &Application::Loop()
{
	return _loop;
}
