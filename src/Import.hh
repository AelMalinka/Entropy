/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_IMPORT_INC
#	define ENTROPY_IMPORT_INC

#	include "Module.hh"
#	include <memory>

	namespace Entropy
	{
		template<typename Interface>
		class Import
		{
			public:
				Import(const std::string &);
				virtual ~Import();
				Interface &operator *();
				Interface *operator->();
			protected:
				std::shared_ptr<Interface> _new() const;
			private:
				Module _module;
				std::shared_ptr<Interface> _obj;
		};
	}

#	include "Import.impl.hh"

#endif
