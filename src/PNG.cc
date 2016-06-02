/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "PNG.hh"

#include "Log.hh"

using namespace Entropy;
using namespace std;

Log::Logger PNG::_log("PNG Image");

PNG::PNG()
	: _handle(), _pixels()
{
	memset(&_handle, 0, sizeof(_handle));
	_handle.version = PNG_IMAGE_VERSION;
	_handle.format = PNG_FORMAT_RGBA;
}

PNG::PNG(const string &name)
	: PNG()
{
	png_image_begin_read_from_file(&_handle, name.c_str());

	_handle.format = PNG_FORMAT_RGBA;
	_pixels.resize(_handle.height * _handle.width);

	png_image_finish_read(&_handle, nullptr, _pixels.data(), PNG_IMAGE_ROW_STRIDE(_handle), nullptr);

	if(_handle.warning_or_error > 0)
	{
		if(_handle.warning_or_error == PNG_IMAGE_WARNING)
			ENTROPY_LOG(_log, Severity::Warning) << _handle.message;
		else
			ENTROPY_THROW(
				PNGException(_handle.message) <<
				PNGFileName(name)
			);
	}
}

void PNG::Write(const string &name)
{
	png_image_write_to_file(&_handle, name.c_str(), false, _pixels.data(), PNG_IMAGE_ROW_STRIDE(_handle), nullptr);

	if(_handle.warning_or_error > 0)
	{
		if(_handle.warning_or_error == PNG_IMAGE_WARNING)
			ENTROPY_LOG(_log, Severity::Warning) << _handle.message;
		else
			ENTROPY_THROW(
				PNGException(_handle.message) <<
				PNGFileName(name)
			);
	}
}

PNG::~PNG()
{
	png_image_free(&_handle);
}

uint32_t &PNG::Height()
{
	return _handle.height;
}

const uint32_t &PNG::Height() const
{
	return _handle.height;
}

uint32_t &PNG::Width()
{
	return _handle.width;
}

const uint32_t &PNG::Width() const
{
	return _handle.width;
}

PNG::iterator PNG::begin() noexcept
{
	return _pixels.begin();
}

PNG::const_iterator PNG::begin() const noexcept
{
	return _pixels.begin();
}

PNG::iterator PNG::end() noexcept
{
	return _pixels.end();
}

PNG::const_iterator PNG::end() const noexcept
{
	return _pixels.end();
}

uint32_t *PNG::data() noexcept
{
	return _pixels.data();
}

const uint32_t *PNG::data() const noexcept
{
	return _pixels.data();
}

uint32_t &PNG::operator [] (const size_t &i)
{
	return _pixels[i];
}

const uint32_t &PNG::operator [] (const size_t &i) const
{
	return _pixels[i];
}

uint8_t PNG::Red(const uint32_t &color)
{
	return (color & RedBits);
}

uint8_t PNG::Green(const uint32_t &color)
{
	return (color & GreenBits) >> 8;
}

uint8_t PNG::Blue(const uint32_t &color)
{
	return (color & BlueBits) >> 16;
}

uint8_t PNG::Alpha(const uint32_t &color)
{
	return (color & AlphaBits) >> 24;
}
