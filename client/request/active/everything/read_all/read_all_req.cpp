#include "read_all_req.h"

read_all_req::read_all_req()
{
}

read_all_req::~read_all_req()
{
}

command_type read_all_req::get_command()
{
	return command_type::READ_ALL_CMD;
}
