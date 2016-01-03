/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_UV_LOOP_INC
#	define ENTROPY_ASIO_UV_LOOP_INC

#	include <uv.h>

	namespace Entropy
	{
		namespace Asio
		{
			namespace UV
			{
				class Loop
				{
					public:
						Loop();
						Loop(const Loop &);
						~Loop();
						Loop &operator = (const Loop &);
						void operator () ();
						uv_loop_t *Handle() const;
					private:
						struct _loop_t {
							uv_loop_t handle;
							size_t count;
						} *_loop;
				};
			}
		}
	}

#endif
