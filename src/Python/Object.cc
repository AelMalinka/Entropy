/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Object.hh"

using namespace Entropy;
using namespace Entropy::Python;
using namespace std;

Object::Object()
	: SharedData<Interpreter>(), _obj(Py_None)
{
	// 2018-02-16 AMR TODO: is this right?
	Py_INCREF(_obj);
}

Object::Object(PyObject *p)
	: SharedData<Interpreter>(), _obj(p)
{
	if(_obj == nullptr)
		ENTROPY_THROW(PythonError("can't have a null python object, use emtpy constructor for None"));

	Py_INCREF(_obj);
}

Object::Object(const long &v)
	: SharedData<Interpreter>(), _obj(nullptr)
{
	// 2018-02-16 AMR TODO: should incref be called?
	_obj = PyLong_FromLong(v);

	if(_obj == nullptr)
		ENTROPY_THROW(PythonError("PyLong failed to initialize"));
}

Object::Object(const double &v)
	: SharedData<Interpreter>(), _obj(nullptr)
{
	// 2018-02-16 AMR TODO: should incref be called?
	_obj = PyFloat_FromDouble(v);

	if(_obj == nullptr)
		ENTROPY_THROW(PythonError("PyFloat failed to initialize"));
}

Object::Object(const string &v)
	: SharedData<Interpreter>(), _obj(nullptr)
{
	// 2018-02-16 AMR TODO: should incref be called?
	_obj = PyUnicode_FromKindAndData(PyUnicode_1BYTE_KIND, static_cast<const void *>(v.c_str()), v.size());

	if(_obj == nullptr)
		ENTROPY_THROW(PythonError("PyUnicode failed to initialize"));
}

Object::Object(const Object &o)
	: SharedData<Interpreter>(), _obj(o._obj)
{
	Py_INCREF(_obj);
}

Object::Object(Object &&o)
	: SharedData<Interpreter>(), _obj(o._obj)
{
	Py_INCREF(_obj);
}

Object::~Object()
{
	if(_obj == nullptr)
		ENTROPY_THROW(PythonError("This should not be possible, Object::_obj is null in ~Object"));

	Py_DECREF(_obj);
}

Object::operator long() const
{
	if(_obj == nullptr || !PyLong_Check(_obj))
		ENTROPY_THROW(PythonError("Object is not integral") <<
			PyHandle(_obj)
		);
	return PyLong_AsLong(_obj);
}

Object::operator double() const
{
	if(_obj == nullptr || !PyFloat_Check(_obj))
		ENTROPY_THROW(PythonError("Object is not floating") <<
			PyHandle(_obj)
		);
	return PyFloat_AsDouble(_obj);
}

Object::operator string() const
{
	if(_obj == nullptr || !PyUnicode_Check(_obj))
		ENTROPY_THROW(PythonError("Object is not a string") <<
			PyHandle(_obj)
		);
	if(PyUnicode_READY(_obj) == -1)
		ENTROPY_THROW(PythonError("Unicode Object is not ready") <<
			PyHandle(_obj)
		);
	
	size_t len = 0;
	char *start = nullptr;
	switch(PyUnicode_KIND(_obj))
	{
		case PyUnicode_1BYTE_KIND:
			len = PyUnicode_GET_LENGTH(_obj);
			start = reinterpret_cast<char *>(PyUnicode_1BYTE_DATA(_obj));
			return string(start, len);
		break;
		default:
			ENTROPY_THROW(PythonError("Unicode Object is unsupported or unknown width") <<
				PyHandle(_obj) <<
				PyUnicodeKind(PyUnicode_KIND(_obj))
			);
	}
}

Object &Object::operator = (const Object &) = default;
Object &Object::operator = (Object &&) = default;

Object Object::get(const string &name)
{
	if(_obj == nullptr)
		ENTROPY_THROW(PythonError("Object is null") <<
			PyHandle(_obj)
		);
	PyObject *o = PyObject_GetAttrString(_obj, name.c_str());
	if(o == nullptr)
		ENTROPY_THROW(PythonError("Attribute not found") <<
			PyHandle(_obj) <<
			PyAttribute(name)
		);

	return o;
}

PyObject *Object::Handle()
{
	return _obj;
}

bool Object::IsNone() const
{
	return _obj == Py_None;
}

void Object::Handle(PyObject *p)
{
	if(p == nullptr)
		ENTROPY_THROW(PythonError("Trying to set Object::Handle to null") <<
			PyHandle(_obj)
		);

	_obj = p;
	Py_INCREF(_obj);
}

using namespace Entropy::Python::detail;

py_tuple::~py_tuple()
{
	Py_DECREF(_val);
}

PyObject *py_tuple::Object() const
{
	return _val;
}

void py_tuple::set_items(std::size_t)
{}
