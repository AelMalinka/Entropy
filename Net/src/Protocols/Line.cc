/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Line.hh"

using namespace Entropy::Net;
using namespace Entropy::Net::Protocols;
using namespace std;

Line::Line()
	: Protocol()
{}

Line::~Line() = default;

void Line::onConnect(Socket &sock)
{
	expecting(sock, "\n");
}

void Line::onData(Socket &sock, string &&line)
{
	line.pop_back();

	if(onMessage(sock, move(line)))
		expecting(sock, "\n");
}
