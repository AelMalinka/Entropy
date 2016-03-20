/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_ASIO_LOOP_INC
#	define ENTROPY_ASIO_LOOP_INC

#	include <boost/any.hpp>

	namespace Entropy
	{
		namespace Asio
		{
			class MainLoop
			{
				public:
					explicit MainLoop();
					MainLoop(const MainLoop &);
					virtual ~MainLoop();
					MainLoop &operator = (const MainLoop &);
					virtual void operator () () = 0;
				protected:
					boost::any &handle();
					const boost::any &handle() const;
				private:
					struct _loop_t {
						boost::any data;
						size_t count;
					} *_loop;
			};
		}
	}

#endif
