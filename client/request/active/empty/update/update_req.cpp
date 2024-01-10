#include "update_req.h"

update_req::update_req()
{
}

update_req::~update_req()
{
}

command_type update_req::get_command()
{
	return command_type::UPDATE_CMD;
}
