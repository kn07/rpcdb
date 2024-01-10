#include "read_all_res.h"

#include "rpcdb.h"
#include <status_codes.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#define SEPARATOR " "
#define SENSOR_INFO "Sensor id: "
#define READ_VALUES_MESSAGE "Data: "

using std::cout;
using std::endl;
using std::runtime_error;
using std::vector;

read_all_res::read_all_res()
{
}

read_all_res::~read_all_res()
{
}

command_type read_all_res::get_command()
{
	return command_type::READ_ALL_CMD;
}

int read_all_res::perform(response *res)
{
	if (res->response_u.read_all.response != status::VALID)
		throw runtime_error(
			status_codes::get(res->response_u.read_all.response));

	sensor_data *src = res->response_u.read_all.data.data_val;
	size_t size = res->response_u.read_all.data.data_len;

	for (int i = 0; i < size; i++) {
		float *val_src = src[i].values.values_val;
		size_t val_size = src[i].values.values_len;
		vector<float> values(val_src, val_src + val_size);

		cout << SENSOR_INFO << src[i].sensor_id << endl;
		cout << READ_VALUES_MESSAGE;

		for (auto j : values)
			cout << j << SEPARATOR;

		cout << endl;
	}

	return status::VALID;
}
