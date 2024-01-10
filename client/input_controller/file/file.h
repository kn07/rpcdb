#pragma once

#include <input_controller.h>

#include <string>

using std::string;

class file_input : public input_controller {
    public:
	file_input(string filename);
	~file_input();
};
