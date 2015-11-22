# Entropy
Entropy is a collection of utilites that have proven to be useful

## Installing
```bash
./autogen.sh
./configure --with(out)-gtest --with(out)-python
make
make check
make install
```
### Dependencies
- Compiler supporting C++14, tested against GCC 5.2.0 and clang 3.7.0
- boost, tested against 1.59.0
optionally
- gtest, compiled and accessible as shared library, tested against 1.7.0
- python 3.3 or newer, tested against 3.5.0, w/ [patch](https://hg.python.org/cpython/raw-rev/d4fcb362f7c6)


### Exception
A heirarchy of exceptions built on top of boost Exception which allow for tag based information to be attached

```C++
ENTROPY_EXCEPTION_BASE(NameofModule, "ModuleName:);
ENTROPY_EXCEPTION(TypeOfError, "Description", NameofModule);
ENTROPY_ERROR_INFO(Extrainfo, std::string);
ENTROPY_ERROR_INFO(MoreExtraInfo, int);

ENTROPY_THROW(TypeOfError("This is a description of THIS error") <<
	ExtraInfo(val) <<
	MoreExtraInfo(info)
);
```
to output all attched error information as well as exception::what()
```C++
try
{
	IWillThrowAnError();
}
catch(std::exception &e)
{
	cout << e << endl;
}
```

###Log
Built on top of boost Log to allow serverity based logging

test/Log/trivial.cc for an example of usage

###Module
Allows for easy definition/implementation of plugins

define an Interface e.g. test/Module/interface.hh

```
Import<interface> module("name of module.so");
```
then just interact w/ the module as if it was a pointer to the interface

###Python
The beginnings of a library for interacting w/ python, intended to allow
the implementation of a Python based module system matching above

###Net
Built on top of boost Asio, allows the definition of Client and/or Server objects,
that use methods as callbacks for events with and without protocol definitions to
translate to application level events

##To Do
- [ ] Implement PyModule
	- [x] Python wrappers
	- [ ] Interface wrapper for python
- [ ] Static implementation of Net
- [ ] parsing of ArgC/ArgV in Entropy::Application
