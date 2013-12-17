/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU General Public License v3
*/

#if !defined ENTROPY_IMPORT_IMPL
#	define ENTROPY_IMPORT_IMPL

#	include "Import.hh"

	namespace Entropy
	{
		template<typename Interface> Import<Interface>::Import(Import<Interface> &&) = default;
		template<typename Interface> Import<Interface>::~Import() = default;
		template<typename Interface> Import<Interface> &Import<Interface>::operator = (const Import<Interface> &) = default;
		template<typename Interface> Import<Interface> &Import<Interface>::operator = (Import<Interface> &&) = default;

		template<typename Interface>
		Import<Interface>::Import(const std::string &name)
			: _module(name), _obj()
		{
			_obj = _new();
		}

		template<typename Interface>
		Import<Interface>::Import(const Import<Interface> &o)
			: _module(o._module), _obj()
		{
			_obj = _new();
		}

		template<typename Interface>
		std::unique_ptr<Interface, std::function<void(void *)>> Import<Interface>::_new() const
		{
			using std::unique_ptr;
			using std::function;

			function<Interface *()> t_new = _module.get<Interface *()>("entropy_new");
			function<void(void *)> t_delete = _module.get<void(void *)>("entropy_delete");

			return unique_ptr<Interface, function<void(void *)>>(t_new(), t_delete);
		}
		template<typename Interface>
		Interface &Import<Interface>::operator * ()
		{
			return *_obj;
		}

		template<typename Interface>
		Interface *Import<Interface>::operator -> ()
		{
			return _obj.get();
		}
	}

#endif
