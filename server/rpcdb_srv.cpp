#include <rpcdb.h>
#include <server.h>

#include <stdexcept>

using std::exception;

extern "C" {
void init_server()
{
	server_::init();
}
}

response *rpc_call_1_svc(request *argp, struct svc_req *rqstp)
{
	static response result;

	try {
		result = server_::execute(argp);
	} catch (exception &e) {
		memset(&result, 0, sizeof result);

		result.type = command_type::BAD_CMD;
		result.response_u.active.response = status::INVALID_REQUEST;
	}

	return &result;
}
