/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_RESOURCE_REFERENCE_INC
#	define ENTROPY_RESOURCE_REFERENCE_INC

#	include "../Exception.hh"

#	include <map>

	namespace Entropy
	{
		namespace Resource
		{
			ENTROPY_EXCEPTION_BASE(Exception, "Resource Exception");

			class Handle;

			class Reference
			{
				public:
					Reference(Handle *);
					Reference(const Reference &);
					Reference(Reference &&);
					virtual ~Reference();
					Reference &operator = (const Reference &);
					Reference &operator = (Reference &&);
					Handle *get();
					Handle &operator * ();
					Handle *operator -> ();
					const Handle *get() const;
					const Handle &operator * () const;
					const Handle *operator -> () const;
					Handle *operator [] (const std::string &);
				private:
					Handle *_handle;
					static std::map<Handle *, unsigned int> _refs;
			};
		}
	}

#endif
