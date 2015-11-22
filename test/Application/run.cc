/*	Copyright 2013 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <cstdlib>
#include "Application.hh"
#include "Exception.hh"

using namespace std;

class Application :
	public Entropy::Application
{
	public:
		Application(int &ArgC, char *ArgV[])
			: Entropy::Application(ArgC, ArgV)
		{}
		~Application() = default;
		void operator () ();
};

ENTROPY_EXCEPTION_BASE(TestFailure, "Test Failure");
ENTROPY_EXCEPTION_BASE(TestSuccess, "Test Success");

int main(int argc, char *argv[]) {
	Application app(argc, argv);

	try {
		app();
	} catch(TestSuccess) {
		return EXIT_SUCCESS;
	} catch(TestFailure) {}

	return EXIT_FAILURE;
}

void Application::operator () () {
	for(int x = 1; x < ArgC(); x++) {
		if(string(ArgV()[x]) == "--success") {
			throw TestSuccess();
		} else if(string(ArgV()[x]) == "--failure") {
			throw TestFailure();
		}
	}
}
