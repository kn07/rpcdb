#include "logout_res.h"

logout_res::logout_res()
{
}

logout_res::~logout_res()
{
}

command_type logout_res::get_command()
{
	return command_type::LOGOUT_CMD;
}

void logout_res::action()
{
	set_logged_in(false);
}
