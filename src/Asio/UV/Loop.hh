/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_UV_LOOP_INC
#	define ENTROPY_ASIO_UV_LOOP_INC

#	include "../Loop.hh"
#	include <uv.h>

	namespace Entropy
	{
		namespace Asio
		{
			namespace UV
			{
				class Loop :
					public Asio::Loop
				{
					public:
						Loop();
						void operator () ();
						uv_loop_t *Handle();
					private:
						class _uv_handle
						{
							public:
								_uv_handle();
								~_uv_handle();
								uv_loop_t *handle();
							private:
								uv_loop_t _handle;
						};
				};
			}
		}
	}

#endif
