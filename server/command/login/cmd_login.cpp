#include "cmd_login.h"

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

cmd_login::cmd_login()
{
}

cmd_login::~cmd_login()
{
}

command_type cmd_login::get_command()
{
	return command_type::LOGIN_CMD;
}

response cmd_login::perform(request *req)
{
	char *username;
	unsigned long key;

	memset(&res, 0, sizeof res);
	res.type = get_command();

	if (user_exists(string(req->request_u.login.username))) {
		res.response_u.login.response = status::EXISTING_USER;

		return res;
	}

	key = rand.next();

	while (session_key_exists(key))
		key = rand.next();

	username = new char[strlen(req->request_u.login.username)];
	strcpy(username, req->request_u.login.username);

	insert_new_user(string(username), key);

	res.response_u.login.response = status::VALID;
	res.response_u.login.session_key = key;

#ifdef DEBUG
	cout << SERVER_OUTPUT << USERNAME_MESSAGE << username
	     << SESSION_KEY_MESSAGE << key << END_MESSAGE << endl;
#endif

	return res;
}
