#include "file.h"

#include <fstream>
#include <stdexcept>

#define ERROR_FILE_OPEN "Cannot open file."

using std::ifstream;
using std::runtime_error;

file_input::file_input(string filename)
{
	input = new ifstream(filename);

	if (input->fail())
		throw runtime_error(ERROR_FILE_OPEN);
}

file_input::~file_input()
{
	delete input;
}
