#include "cmd_logout.h"

#ifdef DEBUG
#include <iostream>

using std::cout;
using std::endl;
#endif

cmd_logout::cmd_logout()
{
}

cmd_logout::~cmd_logout()
{
}

command_type cmd_logout::get_command()
{
	return command_type::LOGOUT_CMD;
}

response cmd_logout::perform(request *req)
{
	unsigned long key;

	memset(&res, 0, sizeof res);

	res.type = get_command();

	if (user_exists(string(req->request_u.logout.username)) == false) {
		res.response_u.active.response = status::INVALID_USER;

		return res;
	}

	key = get_user_key(req->request_u.logout.username);

	if (key != req->request_u.logout.session_key) {
		res.response_u.active.response = status::INVALID_SESSION_KEY;

		return res;
	}

	remove_user(req->request_u.logout.username, key);
	res.response_u.active.response = status::VALID;

	return res;
}
