#include "store_req.h"

store_req::store_req()
{
}

store_req::~store_req()
{
}

command_type store_req::get_command()
{
	return command_type::STORE_CMD;
}
