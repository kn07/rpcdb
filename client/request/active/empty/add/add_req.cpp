#include "add_req.h"

add_req::add_req()
{
}

add_req::~add_req()
{
}

command_type add_req::get_command()
{
	return command_type::ADD_CMD;
}
