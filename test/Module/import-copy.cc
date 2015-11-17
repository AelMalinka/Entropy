/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <iostream>
#include "Import.hh"

#include "interface.hh"

using namespace std;
using namespace Entropy;

int main(int, char **) {
	try
	{
		Import<::tests::Interface> a("module.so");

		a->run();
		(*a)["a"];
		(*a)[0];
		*a = 0;

		Import<::tests::Interface> b(a);

		a->run();
		b->run();
		(*a)["a"];
		(*b)["a"];
		(*a)[0];
		(*b)[0];
		*a = 0;
		*b = 0;

		return EXIT_SUCCESS;
	}
	catch(Exception &e)
	{
		cout << e << endl;
		return EXIT_FAILURE;
	}
}
