/*	Copyright 2015 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_STRING_IMPL
#	define ENTROPY_STRING_IMPL

#	include "String.hh"

#	include <locale>
#	include <codecvt>

	namespace Entropy
	{
		template<>
		std::wstring string_cast(const std::string &i)
		{
			using std::string;
			using std::wstring;
			using std::wstring_convert;
			using std::codecvt_utf8;

			return wstring_convert<codecvt_utf8<wchar_t>>().from_bytes(i);
		}

		template<>
		std::string string_cast(const std::wstring &i)
		{
			using std::string;
			using std::wstring;
			using std::wstring_convert;
			using std::codecvt_utf8;

			return wstring_convert<codecvt_utf8<wchar_t>>().to_bytes(i);
		}
	}

#endif
