/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_TESTS_MODULE_INTERFACE_INC
#	define ENTROPY_TESTS_MODULE_INTERFACE_INC
	
	namespace tests
	{
		class Interface
		{
			public:
				virtual void run() = 0;
				virtual const std::string &operator [] (const std::string &) = 0;
				virtual int operator [] (const int) = 0;
				virtual Interface &operator = (const int) = 0;
		};
	}

#endif
