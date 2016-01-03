/*	Copyright 2010 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
	Application
*/

#if !defined ENTROPY_APPLICATION_INC
#	define ENTROPY_APPLICATION_INC

#	include "Exception.hh"

	namespace Entropy
	{
		class Application
		{
			public:
				Application();
				Application(const int &, char *[]);
				virtual ~Application();
				virtual void operator() () = 0;
			protected:
				const int &ArgC();
				char **ArgV();
			private:
				int _argc;
				char **_argv;
		};
	}

#endif
