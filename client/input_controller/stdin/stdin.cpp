#include "stdin.h"

#include <iostream>

using std::cin;

stdin_input::stdin_input()
{
	input = &cin;
}

stdin_input::~stdin_input()
{
}
