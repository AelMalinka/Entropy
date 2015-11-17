/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "Line.hh"

using namespace Entropy::Net;
using namespace Entropy::Net::Protocols;
using namespace std;

Line::Line()
	: Protocol(), _delim("\n")
{}

Line::Line(const string &delim)
	: Protocol(), _delim(delim)
{}

Line::~Line() = default;

void Line::onConnect(Socket &sock)
{
	expecting(sock, _delim);
}

void Line::onData(Socket &sock, string &&line)
{
	for(size_t x = 0; x < _delim.size(); x++)
		line.pop_back();

	if(onMessage(sock, move(line)))
		expecting(sock, _delim);
}
