#include "get_stat.h"

get_stat_req::get_stat_req()
{
}

get_stat_req::~get_stat_req()
{
}

command_type get_stat_req::get_command()
{
	return command_type::GET_STAT_CMD;
}
