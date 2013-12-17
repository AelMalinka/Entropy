/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
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
				Import(const Import<Interface> &);
				Import(Import<Interface> &&);
				virtual ~Import();
				Import<Interface> &operator = (const Import<Interface> &);
				Import<Interface> &operator = (Import<Interface> &&);
				Interface &operator *();
				Interface *operator->();
			protected:
				std::unique_ptr<Interface, std::function<void(void *)>> _new() const;
			private:
				Module _module;
				std::unique_ptr<Interface, std::function<void(void *)>> _obj;
		};
	}

#	include "Import.impl.hh"

#endif
