#pragma once

#include <rpcdb.h>

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class status_codes {
    private:
	static unordered_map<status, string> *messages;

    private:
	status_codes();

    public:
	static void init();
	static void destroy();
	static string get(status s);
};
