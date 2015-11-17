/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_MODULE_BASE_MODULE
#	define ENTROPY_MODULE_BASE_MODULE

#	include <memory>
#	include "../Exception.hh"

	namespace Entropy
	{
		ENTROPY_EXCEPTION_BASE(ModuleError, "Module Error");
		ENTROPY_EXCEPTION(DeleteError, "entropy_delete", ModuleError);
		ENTROPY_ERROR_INFO(ModuleHandle, void *);
		ENTROPY_ERROR_INFO(ObjectAddress, void *);
		ENTROPY_ERROR_INFO(ModuleName, std::string);

		class BaseModule
		{
			public:
				BaseModule();
				explicit BaseModule(void *, const std::function<void(void *)> &);
				BaseModule(const BaseModule &);
				BaseModule(BaseModule &&);
				virtual ~BaseModule();
				BaseModule &operator = (const BaseModule &);
				BaseModule &operator = (BaseModule &&);
			protected:
				virtual void *open(const std::string &) = 0;
			protected:
				void *handle() const;
			private:
				std::shared_ptr<void> _handle;
		};
	}

#endif
