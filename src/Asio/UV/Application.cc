/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Application.hh"

using namespace Entropy::Asio::UV;

Application::Application()
	: Asio::Application(_loop), _loop()
{}

Application::Application(int ArgC, char *ArgV[])
	: Asio::Application(_loop, ArgC, ArgV), _loop()
{}

Application::~Application() = default;
