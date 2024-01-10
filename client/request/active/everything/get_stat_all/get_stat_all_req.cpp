#include "get_stat_all_req.h"

get_stat_all_req::get_stat_all_req()
{
}

get_stat_all_req::~get_stat_all_req()
{
}

command_type get_stat_all_req::get_command()
{
	return command_type::GET_STAT_ALL_CMD;
}
