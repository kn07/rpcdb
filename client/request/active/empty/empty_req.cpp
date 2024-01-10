#include "empty_req.h"

empty_req::empty_req()
{
	values = new vector<float>();
}

empty_req::~empty_req()
{
	delete values;
}

void empty_req::parse_input(istringstream *input, sensor_data *data)
{
	string token;
	int n;

	if (!(*input >> token))
		throw_param_error();

	data->sensor_id = stoi(token);

	if (!(*input >> token))
		throw_param_error();

	n = stoi(token);

	for (int i = 0; i < n; i++) {
		if (!(*input >> token))
			throw_param_error();

		values->push_back(stof(token));
	}

	data->values.values_len = values->size();
	data->values.values_val = values->data();
}

request empty_req::create(istringstream *stream)
{
	request req;

	values->clear();
	memset(&req, 0, sizeof req);

	req.type = get_command();
	req.request_u.empty.session_key = get_session_key();
	parse_input(stream, &req.request_u.empty.data);

	return req;
}
