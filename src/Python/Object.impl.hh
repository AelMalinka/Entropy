/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_PYTHON_OBJECT_IMPL
#	define ENTROPY_PYTHON_OBJECT_IMPL

#	include "Object.hh"

	namespace Entropy
	{
		namespace Python
		{
			namespace detail
			{
				struct py_tuple
				{
					template<typename ...Args>
					py_tuple(Args...);
					~py_tuple();
					template<typename First, typename ...Args>
					void set_items(std::size_t, First, Args...);
					void set_items(std::size_t);
					PyObject *Object() const;
					private:
						PyObject *_val;
				};
			}

			template<typename ...Args>
			Object Object::operator() (Args... args)
			{
				using detail::py_tuple;

				py_tuple params(args...);
				
				if(!PyCallable_Check(_obj))
					ENTROPY_THROW(PythonError("Object is not callable") <<
						PyHandle(_obj)
					);
				Object ret = PyObject_CallObject(_obj, params.Object());

				Py_XDECREF(ret.Handle());

				return ret;
			}

			template<typename ...Args>
			detail::py_tuple::py_tuple(Args... args)
			{
				_val = PyTuple_New(sizeof...(args));

				if(_val == nullptr)
					ENTROPY_THROW(PythonError("PyTuple_New failed to allocate new tuple"));

				set_items(0, args...);
			}

			template<typename First, typename ...Rest>
			void detail::py_tuple::set_items(std::size_t x, First f, Rest... rest)
			{
				Python::Object o(f);
				Py_INCREF(o.Handle());
				PyTuple_SetItem(_val, x++, o.Handle());
				set_items(x, rest...);
			}
		}
	}

#endif
