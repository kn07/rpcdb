#include "response.h"

#include <client.h>
#include <status_codes.h>

#include <stdexcept>

#define WRONG_RESPONSE "Got wrong response from server."

using std::logic_error;
using std::runtime_error;

interpret_response::interpret_response()
{
}

interpret_response::~interpret_response()
{
}

bool interpret_response::get_logged_in()
{
	return client_::logged_in;
}

void interpret_response::set_logged_in(bool value)
{
	client_::logged_in = value;
}

string interpret_response::get_username()
{
	return *client_::username;
}

void interpret_response::set_username(string username)
{
	*client_::username = username;
}

unsigned long interpret_response::get_session_key()
{
	return client_::session_key;
}

void interpret_response::set_session_key(unsigned long session_key)
{
	client_::session_key = session_key;
}

int interpret_response::interpret(response *res)
{
	if (res->type == command_type::BAD_CMD)
		throw runtime_error(
			status_codes::get(res->response_u.bad.response));

	if (res->type != get_command())
		throw logic_error(WRONG_RESPONSE);

	return perform(res);
}
