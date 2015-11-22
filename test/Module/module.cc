/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Module.hh"
#include <memory>
#include <unordered_map>
#include <iostream>
#include "interface.hh"

using namespace std;

namespace tests {
	class Module :
		public Interface
	{
		public:
			Module();
			~Module();
			void run();
			const string &operator [] (const string &);
			int operator [] (const int);
			Interface &operator = (const int);
	};
}

using namespace ::tests;

Module::Module() = default;
Module::~Module() = default;

void Module::run()
{
	cout << "Module::run()" << endl;
}

const string &Module::operator [] (const string &val)
{
	cout << "Module::operator[]: " << val << endl;
	return val;
}

int Module::operator [] (const int val)
{
	cout << "Module::operator[]: " << val << endl;
	return val;
}

Interface &Module::operator = (const int val)
{
	cout << "Module::operator = " << val << endl;
	return *this;
}

ENTROPY_MODULE(Module)

extern "C" {
void foo()
{
	cout << "module.so:foo()" << endl;
}

void bar()
{
	cout << "module.so:bar()" << endl;
}
}
