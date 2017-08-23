/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Event.hh"

using namespace Entropy;
using namespace std;

Event::Event(const size_t &id)
	: _id(id)
{}

Event::~Event() = default;

const size_t &Event::Id() const
{
	return _id;
}
