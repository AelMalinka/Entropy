/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_RESOURCE_HANDLE_INC
#	define ENTROPY_RESOURCE_HANDLE_INC

#	include "Reference.hh"

#	include <cstdint>

	namespace Entropy
	{
		namespace Resource
		{
			class Handle
			{
				public:
					explicit Handle(const Reference &);
					virtual void load();
					virtual void free();
					virtual bool loaded() const;
					virtual char *data() = 0;
					virtual const char *data() const = 0;
					virtual const std::string &type() const = 0;
					virtual const std::string &name() const = 0;
					virtual std::string filename() const;
					virtual std::string path() const;
				protected:
					virtual void parse(const std::string &) = 0;
					virtual void release() = 0;
				private:
					Reference _root;
					bool _loaded;
			};
		}
	}

#endif
