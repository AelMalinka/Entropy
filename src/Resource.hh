/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_RESOURCE_INC
#	define ENTROPY_RESOURCE_INC

#	include "Resource/Handle.hh"
#	include "Resource/Root.hh"

#	include <functional>
#	include <list>

	namespace Entropy
	{
		namespace Resource
		{
			namespace detail
			{
				class State
				{
					public:
						State();
						Reference get(const std::string &);
						Handle *make(const std::string &, const Reference &);
						void Register(const std::function<Handle *(const std::string &, const Reference &)> &);
						void Register(std::function<Handle *(const std::string &, const Reference &)> &&);
					private:
						Root _root;
						std::list<std::function<Handle *(const std::string &, const Reference &)>> _types;
				};

				static State state;
			}

			Reference get(const std::string &);
			void Register(const std::function<Handle *(const std::string &, const Reference &)> &);
			void Register(std::function<Handle *(const std::string &, const Reference &)> &&);
		}
	}

#	include "Resource/Folder.hh"
#	include "Resource/File.hh"

#endif
