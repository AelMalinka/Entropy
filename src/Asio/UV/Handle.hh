/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_UV_HANDLE_INC
#	define ENTROPY_ASIO_UV_HANDLE_INC

#	include "Loop.hh"

	namespace Entropy
	{
		namespace Asio
		{
			namespace UV
			{
				class Handle
				{
					public:
						Handle(const Handle &) = delete;
						virtual ~Handle();
						bool isActive() const;
						bool isClosing() const;
						MainLoop &Owner();
						const MainLoop &Owner() const;
					protected:
						Handle(Asio::MainLoop &, uv_handle_t *);
						uv_handle_t *handle();
						const uv_handle_t *handle() const;
					private:
						MainLoop &_loop;
						uv_handle_t *_handle;
				};
			}
		}
	}

#endif
