#include "active_res.h"

#include <status_codes.h>

#include <stdexcept>

using std::runtime_error;

active_res::active_res()
{
}

active_res::~active_res()
{
}

void active_res::action()
{
}

int active_res::perform(response *res)
{
	if (res->response_u.active.response != status::VALID)
		throw runtime_error(
			status_codes::get(res->response_u.active.response));

	action();

	return status::VALID;
}
