/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include <iostream>
#include "Import.hh"

#include "interface.hh"

using namespace std;
using namespace Entropy;

int main()
{
	try
	{
		Import<::tests::Interface> a("module.py");

		a->run();
		(*a)["a"];
		(*a)[0];

		return EXIT_SUCCESS;
	}
	catch(exception &e)
	{
		cout << e << endl;
	}

	return EXIT_FAILURE;
}
