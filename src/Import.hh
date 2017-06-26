/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_IMPORT_INC
#	define ENTROPY_IMPORT_INC

#	include "Module.hh"
#	include <memory>

	namespace Entropy
	{
		ENTROPY_EXCEPTION(NullModuleError, "Module is not imported", ModuleError);

		template<typename Interface>
		class Import
		{
			public:
				Import();
				Import(const std::string &);
				virtual ~Import();
				Interface &operator *();
				Interface *operator->();
				void Load(const std::string &);
				void Unload();
			protected:
				std::shared_ptr<Interface> _new();
			private:
				Module _module;
				std::shared_ptr<Interface> _obj;
		};
	}

#	include "Import.impl.hh"

#endif
