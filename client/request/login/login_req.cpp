#include "login_req.h"

#include <stdexcept>
#include <string>

#define LOGIN_ALREADY_ERROR "You are already logged in."
#define LOGIN_NO_USERNAME_ERROR "You must insert a username."

using std::runtime_error;
using std::string;

login_req::login_req()
{
	user = nullptr;
}

login_req::~login_req()
{
	if (user != nullptr)
		delete user;
}

void login_req::check()
{
	if (get_logged_in() == true)
		throw runtime_error(LOGIN_ALREADY_ERROR);
}

request login_req::create(istringstream *stream)
{
	string username;
	request req;

	memset(&req, 0, sizeof req);

	if (!(*stream >> username))
		throw runtime_error(LOGIN_NO_USERNAME_ERROR);

	if (user != nullptr)
		delete user;

	user = new char[username.size()];
	strcpy(user, username.c_str());

	set_username(username);

	req.type = command_type::LOGIN_CMD;
	req.request_u.login.username = user;

	return req;
}
