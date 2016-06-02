/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_RESOURCE_FILE_INC
#	define ENTROPY_RESOURCE_FILE_INC

#	include "Handle.hh"

	namespace Entropy
	{
		namespace Resource
		{
			class File :
				public Handle
			{
				public:
					File(const std::string &, const Reference &);
					char *data();
					const char *data() const;
					const std::string &type() const;
					const std::string &name() const;
				protected:
					void parse(const std::string &);
					void release();
				private:
					std::string _name;
					std::string _data;
					static std::string _type;
			};
		}
	}

#endif
