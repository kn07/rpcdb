#include "delete_res.h"

delete_res::delete_res()
{
}

delete_res::~delete_res()
{
}

command_type delete_res::get_command()
{
	return command_type::DELETE_CMD;
}
