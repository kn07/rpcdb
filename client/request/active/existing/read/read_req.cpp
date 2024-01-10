#include "read_req.h"

read_req::read_req()
{
}

read_req::~read_req()
{
}

command_type read_req::get_command()
{
	return command_type::READ_CMD;
}
