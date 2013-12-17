/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include <cstdlib>
#include <iostream>
#include "Module.hh"

using namespace std;
using namespace Entropy;

int main()
{
	try
	{
		Module a("module.so");

		function<void()> bar = a.get<void()>("bar");

		a.get<void()>("foo")();
		bar();

		Module b(a);
		function<void()> baz = b.get<void()>("bar");

		a.get<void()>("foo")();
		b.get<void()>("foo")();
		bar();
		baz();

		bool success = false;

		try {
			Module c("unknown-module");
		} catch (ModuleError &e) {
			cout << e.what() << endl;
			success = true;
		}

		if(!success) {
			cout << "empty module loaded succesfully" << endl;
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}
	catch(exception &e)
	{
		cout << e << endl;
	}

	return EXIT_FAILURE;
}
