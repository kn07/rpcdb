#include "login_res.h"

#include <status_codes.h>

#include <stdexcept>

#ifdef DEBUG
#include <iostream>

#define SERVER_OUTPUT "[SERVER] "

#define USERNAME_MESSAGE "New user logged in: {"
#define SESSION_KEY_MESSAGE ", "
#define END_MESSAGE "}"

using std::cout;
using std::endl;
#endif

using std::runtime_error;

login_res::login_res()
{
}

login_res::~login_res()
{
}

command_type login_res::get_command()
{
	return command_type::LOGIN_CMD;
}

int login_res::perform(response *res)
{
	if (res->response_u.login.response != status::VALID) {
		set_username(string());

		throw runtime_error(
			status_codes::get(res->response_u.login.response));
	}

#ifdef DEBUG
	cout << SERVER_OUTPUT << USERNAME_MESSAGE << get_username()
	     << SESSION_KEY_MESSAGE << res->response_u.login.session_key
	     << END_MESSAGE << endl;
#endif

	set_logged_in(true);
	set_session_key(res->response_u.login.session_key);

	return status::VALID;
}
