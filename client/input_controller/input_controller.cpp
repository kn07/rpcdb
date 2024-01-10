#include "input_controller.h"

#include <stdexcept>

#define EMPTY_LINE_ERROR "Line is empty."

using std::runtime_error;

input_controller::input_controller()
{
}

input_controller::~input_controller()
{
}

bool input_controller::get_next_line()
{
	return getline(*input, line).good();
}

string input_controller::get_command()
{
	string cmd;

	stream = istringstream{ line };
	cmd = string{};

	if (!(stream >> cmd))
		throw runtime_error(EMPTY_LINE_ERROR);

	return cmd;
}
istringstream *input_controller::get_command_stream()
{
	return &stream;
}
