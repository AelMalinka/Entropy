/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#pragma once

#include <Entropy/Import.hh>

namespace Entropy
{
	namespace Test
	{
		class Interface
		{
			public:
				virtual const std::string &Name() const = 0;
				virtual const std::size_t &Value() const = 0;
		};
	}
}