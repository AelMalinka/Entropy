# Entropy
Entropy is a collection of utilites that have proven to be useful

## Installing
```bash
./autogen.sh
./configure
make
make check
make install
```

### Dependencies
- Compiler supporting C++14, tested against GCC 5.2.0 and clang 3.7.0
- boost, tested against 1.60.0
optionally
- gtest and gmock, compiled and installed as shared library, tested against scm version after merger, TODO
- python 3.3 or newer, tested against 3.5.0, w/ [patch](https://hg.python.org/cpython/raw-rev/d4fcb362f7c6)
- libuv 1.x or newer, tested against 1.8.0

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
to output all attched error information as well as exception::what() when -DDEBUG
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
Built partially ontop of libuv, still under construction

##To Do
- [ ] Implement PyModule
	- [x] Python wrappers
	- [ ] Interface wrapper for python
- [x] Static implementation of Net
- [ ] Implement Asio
	- [ ] TCP
		- [x] Client
		- [ ] Server
	- [ ] UDP
		- [ ] Client
		- [ ] Server
	- [ ] File?
	- [ ] SCTP?
	- [ ] SSDP?
- [ ] Configuration of Log
- [ ] Parsing of ArgC/ArgV in Entropy::Application
