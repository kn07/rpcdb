#pragma once

#include <string>

using std::string;

struct client_ {
    private:
	static bool logged_in;
	static bool cmd_issued;
	static string *username;
	static unsigned long session_key;

	friend class create_request;
	friend class interpret_response;
};
