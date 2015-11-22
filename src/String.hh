/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3'
*/

#if !defined ENTROPY_STRING_INC
#	define ENTROPY_STRING_INC

#	include <string>

	namespace Entropy
	{
		template<typename ostring, typename istring = std::string>
		ostring string_cast(const istring &);
	}

#	include "String.impl.hh"

#endif
