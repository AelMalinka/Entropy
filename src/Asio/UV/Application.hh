/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_UV_APPLICATION_INC
#	define ENTROPY_ASIO_UV_APPLICATION_INC

#	include "../Application.hh"
#	include "Loop.hh"

	namespace Entropy
	{
		namespace Asio
		{
			namespace UV
			{
				class Application :
					public Asio::Application
				{
					public:
						Application();
						Application(int ArgC, char *ArgV[]);
						virtual ~Application();
					private:
						class Loop _loop;
				};
			}
		}
	}

#endif
