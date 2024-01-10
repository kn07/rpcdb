#include "cmd_delete.h"

#include <stdexcept>

using std::exception;

cmd_delete::cmd_delete()
{
}

cmd_delete::~cmd_delete()
{
}

command_type cmd_delete::get_command()
{
	return command_type::DELETE_CMD;
}

response cmd_delete::perform(request *req)
{
	vector<sensor_data> *data;
	int sensor_id;

	memset(&res, 0, sizeof res);
	res.type = get_command();

	try {
		data = get_user_db(req->request_u.existing.session_key);
	} catch (exception &e) {
		res.response_u.active.response = status::INVALID_SESSION_KEY;

		return res;
	}

	sensor_id = req->request_u.existing.sensor_id;

	for (auto it = data->begin(); it != data->end(); it++) {
		if (it->sensor_id == sensor_id) {
			delete[] it->values.values_val;
			data->erase(it);
			res.response_u.active.response = status::VALID;

			return res;
		}
	}

	res.response_u.active.response = status::NO_DATA_FOUND;

	return res;
}
