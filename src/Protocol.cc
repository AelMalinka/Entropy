/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Protocol.hh"

using namespace Entropy::Net;
using namespace std;
using namespace std::placeholders;

Protocol::Protocol()
	: Application()
{}

Protocol::~Protocol() = default;

void Protocol::expecting(Socket &s, const size_t &bytes)
{
	s.Read(bytes);
}

void Protocol::expecting(Socket &s, const string &delim)
{
	s.Read(delim);
}
