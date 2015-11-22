/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_PYTHON_OBJECT_INC
#	define ENTROPY_PYTHON_OBJECT_INC

#	include <Python.h>
#	include <string>
#	include "../Exception.hh"
#	include "Interpreter.hh"

	namespace Entropy
	{
		namespace Python
		{
			ENTROPY_EXCEPTION_BASE(PythonError, "Python Error");
			ENTROPY_ERROR_INFO(PyHandle, PyObject *);
			ENTROPY_ERROR_INFO(PyAttribute, std::string);
			ENTROPY_ERROR_INFO(PyUnicodeKind, unsigned int);
			ENTROPY_ERROR_INFO(Pointer, void *);

			class Object
			{
				public:
					Object();
					Object(PyObject *);
					Object(const long &);
					Object(const double &);
					Object(const std::string &);
					Object(const std::wstring &);
					Object(const Object &);
					Object(Object &&);
					virtual ~Object();
					operator long() const;
					operator double() const;
					operator std::string() const;
					bool IsNone() const;
					Object &operator = (const Object &);
					Object &operator = (Object &&);
					PyObject *Handle();
					Object get(const std::string &);
					template<typename ...Args>
					Object operator () (Args...);
				protected:
					void Handle(PyObject *);
				private:
					static Interpreter _python;
					PyObject *_obj;
			};
		}
	}

#	include "Object.impl.hh"

#endif
