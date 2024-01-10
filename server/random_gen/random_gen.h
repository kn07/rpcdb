#pragma once

#include <chrono>
#include <random>

using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;

class random_gen {
    private:
	random_device device;
	mt19937 range;
	uniform_int_distribution<unsigned long> distribution;

    public:
	random_gen();

	unsigned long next();
};
