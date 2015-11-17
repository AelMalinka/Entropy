/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "BaseModule.hh"
#include <functional>

using namespace Entropy;
using namespace std;
using namespace std::placeholders;

BaseModule::BaseModule()
	: _handle()
{}

BaseModule::BaseModule(void *p, const function<void(void *)> &cl)
	: _handle(p, cl)
{}

BaseModule::~BaseModule()
{}

BaseModule::BaseModule(const BaseModule &) = default;
BaseModule::BaseModule(BaseModule &&) = default;
BaseModule &BaseModule::operator = (const BaseModule &) = default;
BaseModule &BaseModule::operator = (BaseModule &&) = default;

void *BaseModule::handle() const
{
	return _handle.get();
}
