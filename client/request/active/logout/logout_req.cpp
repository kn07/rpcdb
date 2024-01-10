#include "logout_req.h"

#ifdef DEBUG
#include <iostream>

using std::cout;
using std::endl;
#endif

logout_req::logout_req()
{
}

logout_req::~logout_req()
{
}

command_type logout_req::get_command()
{
	return command_type::LOGOUT_CMD;
}

request logout_req::create(istringstream *stream)
{
	request req;

	memset(&req, 0, sizeof req);

	username = get_username();

	req.type = get_command();
	req.request_u.logout.username = &username[0];
	req.request_u.logout.session_key = get_session_key();

	return req;
}
