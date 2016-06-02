/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Resource.hh"

#include <utility>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

using namespace Entropy::Resource;
using namespace Entropy::Resource::detail;
using namespace std;

State::State()
	: _root(), _types()
{
	Register([](auto name, auto root) -> Handle * {
		return new File(name, root);
	});
	Register([](auto name, auto root) -> Handle * {
		using boost::filesystem::path;
		using boost::filesystem::is_directory;

		path p("res" + root->path() + "/" + name);

		if(is_directory(p))
			return new Folder(name, root);

		return nullptr;
	});
}

Reference State::get(const string &name)
{
	using boost::algorithm::split;
	using boost::algorithm::is_any_of;

	Reference last = &_root;
	vector<string> folders;
	split(folders, name, is_any_of("/"));

	for(auto &&f : folders)
		last = last[f];

	return last;
}

void State::Register(const function<Handle *(const string &, const Reference &)> &f)
{
	_types.push_front(f);
}

void State::Register(function<Handle *(const string &, const Reference &)> &&f)
{
	_types.push_front(move(f));
}

Handle *State::make(const string &name, const Reference &root)
{
	for(auto &&f : _types)
	{
		Handle *ret = f(name, root);

		if(ret != nullptr)
			return ret;
	}

	ENTROPY_THROW(Exception("Unknown resource type"));
}

namespace Entropy
{
	namespace Resource
	{
		Reference get(const string & name)
		{
			return state.get(name);
		}

		void Register(const function<Handle *(const string &, const Reference &)> &f)
		{
			state.Register(f);
		}

		void Register(const function<Handle *(const string &, const Reference &)> &&f)
		{
			state.Register(move(f));
		}
	}
}
