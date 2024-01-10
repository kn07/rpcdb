#include "cmd_load.h"

#include <exception>

using std::exception;

cmd_load::cmd_load()
{
}

cmd_load::~cmd_load()
{
}

command_type cmd_load::get_command()
{
	return command_type::LOAD_CMD;
}

response cmd_load::perform(request *req)
{
	memset(&res, 0, sizeof res);
	res.type = get_command();

	vector<sensor_data> *data;

	try {
		data = get_user_db(req->request_u.everything.session_key);
	} catch (exception &e) {
		res.response_u.active.response = status::INVALID_SESSION_KEY;

		return res;
	}

	if (data->size() != 0) {
		res.response_u.active.response = status::INVALID_REQUEST;

		return res;
	}

	for (int i = 0; i < req->request_u.load.sensors.sensors_len; i++) {
		sensor_data insert_sensor;
		sensor_data *sensor =
			&req->request_u.load.sensors.sensors_val[i];

		float *values = new float[sensor->values.values_len];

		memcpy(values, sensor->values.values_val,
		       sensor->values.values_len * sizeof(float));

		insert_sensor.sensor_id = sensor->sensor_id;
		insert_sensor.values.values_len = sensor->values.values_len;
		insert_sensor.values.values_val = values;

		data->push_back(insert_sensor);
	}

	res.response_u.active.response = status::VALID;

	return res;
}
