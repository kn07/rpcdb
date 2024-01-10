#include "call_rpc.h"

#include <stdexcept>

#define RPC_NOT_INIT "Please init call_rpc before use."
#define RPC_PROTOCOL "udp"
#define RPC_CLIENT_INIT_ERROR "RPC client initialization failed."
#define FAILED_CALL_ERROR "call failed"

using std::logic_error;
using std::runtime_error;

call_rpc::call_rpc()
{
	clnt = nullptr;
}

call_rpc::~call_rpc()
{
}

void call_rpc::init(char *hostname)
{
	clnt = clnt_create(hostname, RPC_PROG, RPC_VERS, RPC_PROTOCOL);

	if (clnt == nullptr) {
		clnt_pcreateerror(hostname);
		throw runtime_error(RPC_CLIENT_INIT_ERROR);
	}
}

response *call_rpc::get_response(request req)
{
	if (clnt == nullptr)
		throw logic_error(RPC_NOT_INIT);

	response *res = rpc_call_1(&req, clnt);

	if (res == nullptr) {
		clnt_perror(clnt, FAILED_CALL_ERROR);
		throw runtime_error(FAILED_CALL_ERROR);
	}

	return res;
}
