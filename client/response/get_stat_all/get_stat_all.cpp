#include "get_stat_all.h"

#include <status_codes.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#define ID_FORMAT "Sensor id: "
#define MIN_FORMAT "Minimum value: "
#define MAX_FORMAT "Maximum value: "
#define AVG_FORMAT "Average value: "
#define MED_FORMAT "Median value: "

using std::cout;
using std::endl;
using std::runtime_error;
using std::vector;

get_stat_all_res::get_stat_all_res()
{
}

get_stat_all_res::~get_stat_all_res()
{
}

command_type get_stat_all_res::get_command()
{
	return command_type::GET_STAT_ALL_CMD;
}

int get_stat_all_res::perform(response *res)
{
	if (res->response_u.get_stat_all.response != status::VALID)
		throw runtime_error(
			status_codes::get(res->response_u.read.response));

	sensor_stat *src = res->response_u.get_stat_all.stats.stats_val;
	size_t size = res->response_u.get_stat_all.stats.stats_len;
	vector<sensor_stat> stats(src, src + size);

	for (auto stat : stats) {
		cout << ID_FORMAT << stat.sensor_id << endl;
		cout << MIN_FORMAT << stat.min << endl;
		cout << MAX_FORMAT << stat.max << endl;
		cout << AVG_FORMAT << stat.avg << endl;
		cout << MED_FORMAT << stat.med << endl;
	}

	return status::VALID;
}
