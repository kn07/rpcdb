#include "store_res.h"

#include "rpcdb.h"
#include <status_codes.h>

#include <fstream>
#include <ios>
#include <stdexcept>
#include <vector>

#define DB_EXTENSION ".rpcdb"
#define FILE_ERROR "Error opening database file."

using std::ios;
using std::ofstream;
using std::runtime_error;
using std::vector;

store_res::store_res()
{
}

store_res::~store_res()
{
}

command_type store_res::get_command()
{
	return command_type::STORE_CMD;
}

int store_res::perform(response *res)
{
	if (res->response_u.get_stat_all.response != status::VALID)
		throw runtime_error(
			status_codes::get(res->response_u.read.response));

	ofstream out(get_username() + DB_EXTENSION, ios::binary);

	char *src = reinterpret_cast<char *>(
		res->response_u.read_all.data.data_val);
	size_t size =
		res->response_u.read_all.data.data_len * sizeof(sensor_data);

	if (out.fail())
		throw runtime_error(FILE_ERROR);

	out.write(src, size);
	out.close();

	return status::VALID;
}
