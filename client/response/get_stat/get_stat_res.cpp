#include "get_stat_res.h"

#include <status_codes.h>

#include <iostream>
#include <stdexcept>

#define ID_FORMAT "Sensor id: "
#define MIN_FORMAT "Minimum value: "
#define MAX_FORMAT "Maximum value: "
#define AVG_FORMAT "Average value: "
#define MED_FORMAT "Median value: "

using std::cout;
using std::endl;
using std::runtime_error;

get_stat_res::get_stat_res()
{
}

get_stat_res::~get_stat_res()
{
}

command_type get_stat_res::get_command()
{
	return command_type::GET_STAT_CMD;
}

int get_stat_res::perform(response *res)
{
	if (res->response_u.get_stat.response != status::VALID)
		throw runtime_error(
			status_codes::get(res->response_u.get_stat.response));

	sensor_stat stat = res->response_u.get_stat.stat;

	cout << ID_FORMAT << stat.sensor_id << endl;
	cout << MIN_FORMAT << stat.min << endl;
	cout << MAX_FORMAT << stat.max << endl;
	cout << AVG_FORMAT << stat.avg << endl;
	cout << MED_FORMAT << stat.med << endl;

	return status::VALID;
}
