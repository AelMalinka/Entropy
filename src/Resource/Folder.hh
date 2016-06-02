/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_RESOURCE_FOLDER_INC
#	define ENTROPY_RESOURCE_FOLDER_INC

#	include "Handle.hh"

	namespace Entropy
	{
		namespace Resource
		{
			class Folder :
				public Handle
			{
				public:
					Folder(const std::string &, const Reference &);
					virtual void load();
					virtual void free();
					virtual bool loaded() const;
					virtual char *data();
					virtual const char *data() const;
					virtual const std::string &type() const;
					virtual const std::string &name() const;
					virtual Handle *operator [] (const std::string &);
				protected:
					virtual void parse(const std::string &);
					virtual void release();
				private:
					std::string _name;
					std::map<std::string, Handle *> _contents;
					bool _loaded;
					static std::string _type;
			};

			ENTROPY_ERROR_INFO(LowerException, std::exception);
		}
	}

#endif
