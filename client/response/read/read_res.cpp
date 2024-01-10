#include "read_res.h"

#include <status_codes.h>

#include <iostream>
#include <stdexcept>
#include <vector>

#define SEPARATOR " "
#define READ_VALUES_MESSAGE "Data: "

using std::cout;
using std::endl;
using std::runtime_error;
using std::vector;

read_res::read_res()
{
}

read_res::~read_res()
{
}

command_type read_res::get_command()
{
	return command_type::READ_CMD;
}

int read_res::perform(response *res)
{
	if (res->response_u.read.response != status::VALID)
		throw runtime_error(
			status_codes::get(res->response_u.read.response));

	float *src = res->response_u.read.values.values_val;
	size_t size = res->response_u.read.values.values_len;
	vector<float> values(src, src + size);

	cout << READ_VALUES_MESSAGE;

	for (float i : values)
		cout << i << SEPARATOR;

	cout << endl;

	memset(&values, 0, sizeof values);

	return status::VALID;
}
