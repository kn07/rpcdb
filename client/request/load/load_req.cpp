#include "load_req.h"

#include "rpcdb.h"
#include <fstream>
#include <ios>
#include <stdexcept>

#define DB_EXTENSION ".rpcdb"
#define LOAD_FAILED "Load command failed."
#define FILE_OPEN_ERROR "Error opening file."

using std::ifstream;
using std::ios;
using std::runtime_error;
using std::streampos;

load_req::load_req()
{
	db = nullptr;
}

load_req::~load_req()
{
	delete db;
}

void load_req::check()
{
	if (!get_logged_in())
		throw_login_error();
	if (get_cmd_issued())
		throw runtime_error(LOAD_FAILED);
}

request load_req::create(istringstream *stream)
{
	request req;
	ifstream input;
	streampos file_size;
	int n;

	memset(&req, 0, sizeof req);

	input = ifstream(get_username() + DB_EXTENSION, ios::binary);
	input.unsetf(ios::skipws);

	if (input.fail())
		throw runtime_error(FILE_OPEN_ERROR);

	input.seekg(0, ios::end);
	file_size = input.tellg();
	input.seekg(0, ios::beg);

	if (db != nullptr)
		delete[] db;

	n = file_size / sizeof(sensor_data);
	db = new sensor_data[n];

	input.read(reinterpret_cast<char *>(db), file_size);

	input.close();

	req.type = command_type::LOAD_CMD;
	req.request_u.load.session_key = get_session_key();
	req.request_u.load.sensors.sensors_len = n;
	req.request_u.load.sensors.sensors_val = db;

	return req;
}
