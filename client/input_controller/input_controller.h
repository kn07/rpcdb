#pragma once

#include <sstream>
#include <unordered_map>

using std::istream;
using std::istringstream;
using std::string;

class input_controller {
    protected:
	istream *input;
	string line;
	istringstream stream;

    protected:
	input_controller();

    public:
	virtual ~input_controller();

	bool get_next_line();
	string get_command();
	istringstream *get_command_stream();
};
