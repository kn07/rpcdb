#include "request.h"

#include <client.h>

#include <stdexcept>

#define LOGIN_ERROR "You must login first."

using std::runtime_error;

create_request::create_request()
{
}

create_request::~create_request()
{
}

bool create_request::get_logged_in()
{
	return client_::logged_in;
}

void create_request::set_logged_in(bool value)
{
	client_::logged_in = value;
}

bool create_request::get_cmd_issued()
{
	return client_::cmd_issued;
}

void create_request::set_cmd_issued(bool value)
{
	client_::cmd_issued = value;
}

string create_request::get_username()
{
	return *client_::username;
}

void create_request::set_username(string username)
{
	*client_::username = username;
}

unsigned long create_request::get_session_key()
{
	return client_::session_key;
}

void create_request::set_session_key(unsigned long session_key)
{
	client_::session_key = session_key;
}

void create_request::throw_login_error()
{
	throw runtime_error(LOGIN_ERROR);
}

request create_request::generate(istringstream *stream)
{
	check();

	return create(stream);
}
