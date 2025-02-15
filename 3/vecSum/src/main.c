#include <stdio.h>
#include <immintrin.h>
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

	//parse parameter: size of the vector in KiB
	array_size_bytes = strtoull(argv[1], NULL, 10) * 1024;
	//parse parameter: runtime in milliseconds
	minimal_runtime_ms = strtoull(argv[2], NULL, 10);
	//allocate memory and initialize it with nonzero values
	float* array = (float*)_mm_malloc(array_size_bytes, 64);
	int32_t array_size = array_size_bytes / sizeof(float);
	
	for(int32_t i = 0; i < array_size; i++){
		array[i] = (float)i;
	}

	// float result = 0.f;
	
	for(runs = 1u; actual_runtime_us < minimal_runtime_ms * 1000; runs = runs << 1u) {
		start = get_time_micros();
		for(uint64_t i = 0u; i < runs; i++) {
			vec_sum(array, array_size);
		}
		stop  = get_time_micros();
		actual_runtime_us = stop - start;
	}

	runs /= 2; // TODO Explain/comment why this is necessary

	// result check
	// printf("%f, %d\n", result, array_size*(array_size-1)/2);
 
	//calculate and print
	adds_per_second = (double)array_size / actual_runtime_us * runs * 1e6; // Measured performance as floating point additions per second

	// The ouput format:
	// 	1. uint64_t array size in KiB
	// 	2. double   number of additions per second
	// 	3. uint64_t actual runtime in milliseconds
	// 	4. uint64_t minimal runtime in milliseconds
	fprintf(stdout, "%" PRIu64 ",%lf,%" PRIu64 ",%" PRIu64 "\n", array_size_bytes/1024, adds_per_second, actual_runtime_us/1000, minimal_runtime_ms);

	free(array);

	return 0;
}

