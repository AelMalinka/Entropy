/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include <cstdlib>
#include <iostream>
#include "Import.hh"

#include "Interface.hh"

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

		return EXIT_SUCCESS;
	}
	catch(Exception &e)
	{
		cout << e << endl;
		return EXIT_FAILURE;
	}
}
