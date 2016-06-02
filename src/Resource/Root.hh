/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_RESOURCE_ROOT_INC
#	define ENTROPY_RESOURCE_ROOT_INC

#	include "Folder.hh"

	namespace Entropy
	{
		namespace Resource
		{
			class Root :
				public Folder
			{
				public:
					Root();
					void free();
					std::string filename() const;
					std::string path() const;
				private:
					static constexpr auto _name = "root";
			};
		}
	}

#endif
