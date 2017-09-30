/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Interface.hh"

using namespace std;
using namespace Entropy::Test;

class Module :
	public Interface
{
	public:
		Module();
		const string &Name() const;
		const size_t &Value() const;
	private:
		string _name;
		size_t _value;
};

Module::Module()
	: _name("Windows Module"s), _value(12)
{}

const string &Module::Name() const
{
	return _name;
}

const size_t &Module::Value() const
{
	return _value;
}

ENTROPY_MODULE(Module)
