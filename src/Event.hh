/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_EVENT_INC
#	define ENTROPY_EVENT_INC

#	include <cstdint>

	namespace Entropy
	{
		class Event
		{
			public:
				Event(const std::size_t &);
				virtual ~Event();
				const std::size_t &Id() const;
			private:
				std::size_t _id;
		};
	}

#endif
