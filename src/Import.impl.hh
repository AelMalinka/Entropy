/*	Copyright 2013 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_IMPORT_IMPL
#	define ENTROPY_IMPORT_IMPL

#	include "Import.hh"

	namespace Entropy
	{
		template<typename Interface> Import<Interface>::~Import() = default;

		template<typename Interface>
		Import<Interface>::Import(const std::string &name)
			: _module(name), _obj()
		{
			_obj = _new();
		}

		template<typename Interface>
		std::shared_ptr<Interface> Import<Interface>::_new() const
		{
			using std::shared_ptr;
			using std::function;

			function<Interface *()> t_new = _module.get<Interface *()>("entropy_new");
			function<void(void *)> t_delete = _module.get<void(void *)>("entropy_delete");

			Interface *ptr = nullptr;
			
			try
			{
				ptr = t_new();

				return shared_ptr<Interface>(ptr, t_delete);
			}
			catch(...)
			{
				if(ptr != nullptr)
					t_delete(ptr);
			}

			return shared_ptr<Interface>(nullptr, t_delete);
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
