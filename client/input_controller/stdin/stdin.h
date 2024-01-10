#pragma once

#include <input_controller.h>

class stdin_input : public input_controller {
    public:
	stdin_input();
	~stdin_input();
};
