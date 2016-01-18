/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_APPLICATION_INC
#	define ENTROPY_ASIO_APPLICATION_INC

#	include "../Application.hh"
#	include "Loop.hh"

	namespace Entropy
	{
		namespace Asio
		{
			class Application :
				public Entropy::Application
			{
				public:
					Application(Loop &);
					Application(Loop &, int ArgC, char *ArgV[]);
					virtual ~Application();
					virtual void operator () ();
					Entropy::Asio::Loop &Loop();
				private:
					Entropy::Asio::Loop &_loop;
			};
		}
	}

#endif
