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
			namespace internal
			{
				struct py_tuple
				{
					template<typename ...Args>
					py_tuple(Args...);
					~py_tuple();
					PyObject *Object() const;
					private:
						PyObject *_val;
				};

				template<typename ...Args> inline void pass(Args && ...){}
			}

			template<typename ...Args>
			Object Object::operator() (Args... args)
			{
				using internal::py_tuple;

				py_tuple params(args...);
				
				if(!PyCallable_Check(_obj))
					ENTROPY_THROW(PythonError("Object is not callable") <<
						PyHandle(_obj)
					);
				Object ret = PyObject_CallObject(_obj, params.Object());

				return ret;
			}

			template<typename ...Args>
			internal::py_tuple::py_tuple(Args... args)
			{
				_val = PyTuple_New(sizeof...(args));
				std::size_t x = 0;

				pass(PyTuple_SetItem(_val, x++, args)...);
			}
		}
	}

#endif
