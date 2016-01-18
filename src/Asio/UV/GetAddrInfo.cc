/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "GetAddrInfo.hh"
#include "../../Exception.hh"
#include <cstring>

using namespace Entropy::Asio::UV;
using namespace Entropy;
using namespace std;

GetAddrInfo::GetAddrInfo(Asio::Loop &loop, const function<void (struct addrinfo *)> &cb, const string &host, const string &service, int type)
	: _req(), _cb(cb), _hints()
{
	_req.data = this;

	memset(&_hints, 0, sizeof(_hints));
	_hints.ai_family = AF_UNSPEC;
	_hints.ai_flags = AI_PASSIVE;
	_hints.ai_socktype = type;

	int ret = uv_getaddrinfo(dynamic_cast<Loop &>(loop).Handle(), &_req, _entropy_asio_uv_getaddrinfo_cb, host.data(), service.data(), &_hints);
	if(ret < 0)
		ENTROPY_THROW(
			GeneralFailure("GetAddrInfo failed") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

GetAddrInfo::~GetAddrInfo()
{
	uv_cancel((uv_req_t *)&_req);
}

void GetAddrInfo::callback(struct addrinfo *res)
{
	_cb(res);
}

void _entropy_asio_uv_getaddrinfo_cb(uv_getaddrinfo_t *req, int status, struct addrinfo *res)
{
	// 2016-01-04 AMR NOTE: canceled before finished, not an error
	if(status == UV_ECANCELED)
	{}
	else if(status < 0)
	{
		ENTROPY_THROW(
			GeneralFailure("GetAddrInfo failed") <<
			SystemErrorCode(error_code(-status, system_category())) <<
			SystemError(uv_strerror(status))
		);
	}
	else
	{
		try
		{
			((GetAddrInfo *)req->data)->callback(res);
			uv_freeaddrinfo(res);
		}
		catch(...)
		{
			uv_freeaddrinfo(res);
			throw;
		}
	}
}
