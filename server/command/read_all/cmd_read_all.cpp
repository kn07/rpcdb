#include "cmd_read_all.h"

#include <exception>

using std::exception;

cmd_read_all::cmd_read_all()
{
	sensors = nullptr;
}

cmd_read_all::~cmd_read_all()
{
	if (sensors != nullptr)
		delete[] sensors;
}

command_type cmd_read_all::get_command()
{
	return command_type::READ_ALL_CMD;
}

response cmd_read_all::perform(request *req)
{
	vector<sensor_data> *data;
	int sensor_id;

	memset(&res, 0, sizeof res);
	res.type = get_command();

	try {
		data = get_user_db(req->request_u.everything.session_key);
	} catch (exception &e) {
		res.response_u.read_all.response = status::INVALID_SESSION_KEY;

		return res;
	}

	if (sensors != nullptr)
		delete[] sensors;

	sensors = new sensor_data[data->size()];
	memcpy(sensors, data->data(), data->size() * sizeof(sensor_data));

	res.response_u.read_all.data.data_val = sensors;
	res.response_u.read_all.data.data_len = data->size();

	res.response_u.read_all.response = status::VALID;

	return res;
}
