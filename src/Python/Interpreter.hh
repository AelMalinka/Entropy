/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_PYTHON_INTERPRETER_INC
#	define ENTROPY_PYTHON_INTERPRETER_INC

#	include <Python.h>
#	include <cstddef>

	namespace Entropy
	{
		namespace Python
		{
			class Interpreter
			{
				public:
					Interpreter();
					~Interpreter();
				private:
					static std::size_t _count;
			};
		}
	}

#endif
