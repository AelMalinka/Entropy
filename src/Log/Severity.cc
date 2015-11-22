/*	Copyright 2014 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Severity.hh"

#include <vector>

using namespace std;
using namespace Entropy::Log;

ostream &Entropy::Log::operator << (ostream &os, const Severity &s)
{
	const vector<string> names = {
		"Trace",
		"Debug",
		"Info",
		"Warning",
		"Error",
		"Critical",
		"Fatal"
	};
	auto l = static_cast<size_t>(s);

	if(l < names.size())
		os << names[l];
	else
		os << l;

	return os;
}
