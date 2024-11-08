#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "vec_sum.h"
#include "get_time.h"

static void usage_msg(void) {
	fprintf(stderr, "Usage: ./vecSum <array size in kiB> <minimal runtime in milliseconds>\n");
	return;
}

int main(int argc, char *argv[]) {
	uint64_t minimal_runtime_ms = 0u;
	uint64_t actual_runtime_us  = 0u;
	uint64_t array_size_bytes   = 0u;  // The allocated array size in bytes
	uint64_t runs               = 0u;
	uint64_t start              = 0u;
	uint64_t stop               = 0u;
	double   adds_per_second    = 0u;

	if(argc != 3 || argv == NULL) {
		usage_msg();
		return -1;
	}

	//TODO: parse parameter: size of the vector in KiB
	//TODO: parse parameter: runtime in milliseconds
	//TODO: allocate memory and initialize it with nonzero values

	for(runs = 1u; actual_runtime_us < minimal_runtime_ms * 1000; runs = runs << 1u) {
		start = get_time_micros();
		for(uint64_t i = 0u; i < runs; i++) {
			// TODO
			vec_sum(NULL, 0);
		}
		stop  = get_time_micros();
		actual_runtime_us = stop - start;
	}
	runs /= 2; // TODO Explain/comment why this is necessary
 
	//TODO: calculate and print
	adds_per_second = 0.0; // Measured performance as floating point additions per second

	// The ouput format:
	// 	1. uint64_t array size in bytes
	// 	2. double   number of additions per second
	// 	3. uint64_t actual runtime in milliseconds
	// 	4. uint64_t minimal runtime in milliseconds
	fprintf(stdout, "%" PRIu64 ",%lf,%" PRIu64 ",%" PRIu64 "\n", array_size_bytes, adds_per_second, actual_runtime_us/1000, minimal_runtime_ms);

	return 0;
}

