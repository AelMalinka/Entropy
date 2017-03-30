/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "String.hh"

#include <locale>
#include <codecvt>

using namespace std;

namespace Entropy {
	template<>
	string string_cast(const u32string &o)
	{
		wstring_convert<codecvt_utf8<char32_t>, char32_t> cv;
		return cv.to_bytes(o);
	}

	template<>
	string string_cast(const u16string &o)
	{
		wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> cv;
		return cv.to_bytes(o);
	}

	template<>
	u32string string_cast(const string &o)
	{
		wstring_convert<codecvt_utf8<char32_t>, char32_t> cv;
		return cv.from_bytes(o);
	}

	template<>
	u16string string_cast(const string &o)
	{
		wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> cv;
		return cv.from_bytes(o);
	}
}
