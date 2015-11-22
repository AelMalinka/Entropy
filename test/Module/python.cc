/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

// 2015-11-20 AMR NOTE: python C/API states it requires being included first
#include "Import.hh"
#include <cstdlib>
#include <iostream>

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
