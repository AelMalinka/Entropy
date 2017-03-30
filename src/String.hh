/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3'
*/

#if !defined ENTROPY_STRING_INC
#	define ENTROPY_STRING_INC

#	include <string>

	namespace Entropy
	{
		template<typename ostring = std::string, typename istring>
		ostring string_cast(const istring &);
	}

#endif
