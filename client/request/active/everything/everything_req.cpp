#include "everything_req.h"

everything_req::everything_req()
{
}
everything_req::~everything_req()
{
}

request everything_req::create(istringstream *stream)
{
	request req;

	memset(&req, 0, sizeof req);

	req.type = get_command();
	req.request_u.existing.session_key = get_session_key();

	return req;
}
