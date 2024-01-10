#include "cmd_add.h"

#include <stdexcept>
#include <vector>

using std::exception;
using std::vector;

cmd_add::cmd_add()
{
}
cmd_add::~cmd_add()
{
}

command_type cmd_add::get_command()
{
	return command_type::ADD_CMD;
}

response cmd_add::perform(request *req)
{
	vector<sensor_data> *data;
	sensor_data req_data;

	memset(&res, 0, sizeof res);
	res.type = get_command();

	try {
		data = get_user_db(req->request_u.empty.session_key);
	} catch (exception &e) {
		res.response_u.active.response = status::INVALID_SESSION_KEY;

		return res;
	}

	req_data = req->request_u.empty.data;

	for (auto it = data->begin(); it != data->end(); it++) {
		if (it->sensor_id == req_data.sensor_id) {
			res.response_u.active.response =
				status::EXISTING_RECORD;

			return res;
		}
	}

	float *values = new float[req_data.values.values_len];
	memcpy(values, req_data.values.values_val,
	       req_data.values.values_len * sizeof(float));

	req_data.values.values_val = values;

	data->push_back(req_data);
	res.response_u.active.response = status::VALID;

	return res;
}
