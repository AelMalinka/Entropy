/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_EXCEPTION_INC
#	define ENTROPY_MODULE_EXCEPTION_INC

#	include "../Exception.hh"

	namespace Entropy
	{
		ENTROPY_EXCEPTION_BASE(ModuleError, "Module Error");
		ENTROPY_EXCEPTION(DeleteError, "entropy_delete", ModuleError);
		ENTROPY_ERROR_INFO(ModuleHandle, void *);
		ENTROPY_ERROR_INFO(ObjectAddress, void *);
		ENTROPY_ERROR_INFO(ModuleName, std::string);
	}

#endif
