/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "GetNameInfo.hh"
#include <cstring>

using namespace Entropy::Asio::UV;
using namespace Entropy;
using namespace std;

GetNameInfo::GetNameInfo(Loop &loop, const function<void (const string &, const string &)> &cb, const Stream &sock)
	: _req(), _cb(cb)
{
	_req.data = this;

	struct sockaddr s = sock.Socket();
	int ret = uv_getnameinfo(loop.Handle(), &_req, _entropy_asio_uv_getnameinfo_cb, &s, 0);
	if(ret < 0)
		ENTROPY_THROW(
			GeneralFailure("GetNameInfo failed") <<
			SystemErrorCode(error_code(-ret, system_category())) <<
			SystemError(uv_strerror(ret))
		);
}

GetNameInfo::~GetNameInfo()
{
	uv_cancel((uv_req_t *)&_req);
}

void GetNameInfo::callback(const string &h, const string &s)
{
	_cb(h, s);
}

void _entropy_asio_uv_getnameinfo_cb(uv_getnameinfo_t *req, int status, const char *host, const char *port)
{
	// 2016-01-04 AMR NOTE: canceled before finished, not an error
	// 2016-01-04 AMR NOTE: cancel happens in destructor DO NOT THROW
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
		((GetNameInfo *)req->data)->callback(host, port);
	}
}
