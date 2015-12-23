/*	Copyright 2010 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Pulbic License v3
*/

#include "Application.hh"

using namespace Entropy;

Application::Application(int &c, char *v[])
	: _argc(c), _argv(v)
{}

Application::~Application() = default;

const int &Application::ArgC()
{
	return _argc;
}

char **Application::ArgV()
{
	return _argv;
}
