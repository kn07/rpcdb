#include "delete_req.h"

delete_req::delete_req()
{
}

delete_req::~delete_req()
{
}

command_type delete_req::get_command()
{
	return command_type::DELETE_CMD;
}
