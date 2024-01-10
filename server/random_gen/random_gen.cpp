#include "random_gen.h"

#include <limits.h>

random_gen::random_gen()
{
	mt19937::result_type seed =
		device() ^
		((std::mt19937::result_type)
			 std::chrono::duration_cast<std::chrono::seconds>(
				 std::chrono::system_clock::now()
					 .time_since_epoch())
				 .count() +
		 (std::mt19937::result_type)
			 std::chrono::duration_cast<std::chrono::microseconds>(
				 std::chrono::high_resolution_clock::now()
					 .time_since_epoch())
				 .count());
	range = mt19937(seed);
	distribution = uniform_int_distribution<unsigned long>(
		static_cast<unsigned long>(0), ULONG_MAX);
}

unsigned long random_gen::next()
{
	return distribution(range);
}
