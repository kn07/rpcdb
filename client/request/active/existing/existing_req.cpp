#include "existing_req.h"

existing_req::existing_req()
{
}

existing_req::~existing_req()
{
}

void existing_req::parse_input(istringstream *stream, int *sensor_id)
{
	string token;

	if (!(*stream >> token))
		throw_param_error();

	*sensor_id = stoi(token);
}

request existing_req::create(istringstream *stream)
{
	request req;

	memset(&req, 0, sizeof req);

	req.type = get_command();
	req.request_u.existing.session_key = get_session_key();
	parse_input(stream, &req.request_u.existing.sensor_id);

	return req;
}
