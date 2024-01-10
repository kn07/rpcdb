#pragma once

#include <rpcdb.h>

#include <string>

using std::string;

class call_rpc {
    private:
	CLIENT *clnt;

    public:
	call_rpc();
	~call_rpc();

	void init(char *hostname);
	response *get_response(request req);
};
