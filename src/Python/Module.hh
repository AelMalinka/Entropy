/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_PYTHON_MODULE_INC
#	define ENTROPY_PYTHON_MODULE_INC

#	include "Object.hh"

	namespace Entropy
	{
		namespace Python
		{
			ENTROPY_ERROR_INFO(ModuleName, std::string);

			class Module :
				public Object
			{
				public:
					Module(const std::string &);
					virtual ~Module();
			};
		}
	}

#endif
