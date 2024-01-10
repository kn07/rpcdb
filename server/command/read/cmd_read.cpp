#include "cmd_read.h"

#include <exception>

using std::exception;

cmd_read::cmd_read()
{
}

cmd_read::~cmd_read()
{
}

command_type cmd_read::get_command()
{
	return command_type::READ_CMD;
}

response cmd_read::perform(request *req)
{
	vector<sensor_data> *data;
	int sensor_id;

	memset(&res, 0, sizeof res);
	res.type = get_command();

	try {
		data = get_user_db(req->request_u.existing.session_key);
	} catch (exception &e) {
		res.response_u.read.response = status::INVALID_SESSION_KEY;

		return res;
	}

	sensor_id = req->request_u.existing.sensor_id;

	for (auto it = data->begin(); it != data->end(); it++) {
		if (it->sensor_id == sensor_id) {
			res.response_u.read.response = status::VALID;
			res.response_u.read.values.values_val =
				it->values.values_val;
			res.response_u.read.values.values_len =
				it->values.values_len;

			return res;
		}
	}

	res.response_u.read.response = status::NO_DATA_FOUND;

	return res;
}
