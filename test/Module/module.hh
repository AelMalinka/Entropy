/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_TESTS_MODULE_MODULE_INC
#	define ENTROPY_TESTS_MODULE_MODULE_INC

#	include "interface.hh"

	namespace tests
	{
		class Module :
			public Interface
		{
			public:
				Module();
				~Module();
				void run();
				const std::string &operator [] (const std::string &);
				int operator [] (const int);
				Interface &operator = (const int);
			protected:
			private:
		};
	}

	extern "C" {
		::tests::Module *entropy_new();
		void entropy_delete(void *);
		void foo();
		void bar();
	}
	
#endif
