/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_PNG_INC
#	define ENTROPY_PNG_INC

#	include <vector>
#	include <cstdint>
#	include <png.h>

#	include "Exception.hh"
#	include "Log/Logger.hh"

	namespace Entropy
	{
		class PNG
		{
			public:
				PNG();
				explicit PNG(const std::string &);
				~PNG();
				void Write(const std::string &);
				std::uint32_t &Height();
				const std::uint32_t &Height() const;
				std::uint32_t &Width();
				const std::uint32_t &Width() const;
				typedef std::vector<std::uint32_t>::iterator iterator;
				typedef std::vector<std::uint32_t>::const_iterator const_iterator;
				iterator begin() noexcept;
				const_iterator begin() const noexcept;
				iterator end() noexcept;
				const_iterator end() const noexcept;
				std::uint32_t *data() noexcept;
				const std::uint32_t *data() const noexcept;
				std::uint32_t &operator [] (const std::size_t &);
				const std::uint32_t &operator [] (const std::size_t &) const;
				static constexpr const std::uint32_t RedBits = 0xFF;
				static constexpr const std::uint32_t GreenBits = 0xFF00;
				static constexpr const std::uint32_t BlueBits = 0xFF0000;
				static constexpr const std::uint32_t AlphaBits = 0xFF000000;
				static std::uint8_t Red(const std::uint32_t &);
				static std::uint8_t Green(const std::uint32_t &);
				static std::uint8_t Blue(const std::uint32_t &);
				static std::uint8_t Alpha(const std::uint32_t &);
			private:
				Log::Logger _log;
				png_image _handle;
				std::vector<std::uint32_t> _pixels;
		};

		ENTROPY_EXCEPTION_BASE(PNGException, "PNG Exception");
		ENTROPY_ERROR_INFO(PNGFileName, std::string);
	}

#endif
