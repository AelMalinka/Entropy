/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_MODULE_PYMODULE_IMPL
#	define ENTROPY_MODULE_PYMODULE_IMPL

#	include "PyModule.hh"
#	include <functional>

	namespace Entropy
	{
		namespace detail
		{
			template<typename F>
			struct wrapper
			{};

			template<typename R, typename ...Args>
			struct wrapper<R(Args...)>
			{
				wrapper(const std::function<Python::Object(Args...)> &);
				R operator () (Args...);
				private:
					std::function<Python::Object(Args...)> _f;
			};

			template<typename R, typename ...Args>
			struct wrapper<R *(Args...)>
			{
				wrapper(const std::function<Python::Object(Args...)> &);
				R *operator () (Args...);
				private:
					std::function<Python::Object(Args...)> _f;
			};

			template<typename ...Args>
			struct wrapper<void(Args...)>
			{
				wrapper(const std::function<void(Args...)> &r);
				void operator () (Args...);
				private:
					std::function<void(Args...)> _f;
			};
		}

		template<typename F>
		std::function<F> PyModule::get(const std::string &name) const
		{
			using detail::wrapper;
			using Python::Module;

			return wrapper<F>();
		}

		template<typename R, typename ...Args>
		detail::wrapper<R(Args...)>::wrapper(const std::function<Python::Object(Args...)> &f)
			: _f(f)
		{}

		template<typename R, typename ...Args>
		R detail::wrapper<R(Args...)>::operator () (Args... args)
		{
			return _f(args...);
		}

		template<typename ...Args>
		detail::wrapper<void(Args...)>::wrapper(const std::function<void(Args...)> &f)
			: _f(f)
		{}

		template<typename ...Args>
		void detail::wrapper<void(Args...)>::operator () (Args... args)
		{
			_f(args...);
		}

		template<typename R, typename ...Args>
		detail::wrapper<R *(Args...)>::wrapper(const std::function<Python::Object(Args...)> &f)
			: _f(f)
		{}

		template<typename R, typename ...Args>
		R *detail::wrapper<R *(Args...)>::operator () (Args...)
		{
			ENTROPY_THROW(ModuleError("Not yet supported, importing python"));
		}
	}

#endif
