#include "cmd_store.h"

#include <exception>

using std::exception;

cmd_store::cmd_store()
{
	sensors = nullptr;
}

cmd_store::~cmd_store()
{
	if (sensors != nullptr)
		delete[] sensors;
}

command_type cmd_store::get_command()
{
	return command_type::STORE_CMD;
}

response cmd_store::perform(request *req)
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
