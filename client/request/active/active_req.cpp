#include "active_req.h"

#include <stdexcept>

#define WRONG_PARAM_ERROR "Not enough parameters for the issued command."

using std::runtime_error;

active_req::active_req()
{
}

active_req::~active_req()
{
}

void active_req::throw_param_error()
{
	throw runtime_error(WRONG_PARAM_ERROR);
}

void active_req::check()
{
	if (get_logged_in() == false)
		throw_login_error();
}
