#include <immintrin.h>
#include <string.h>
#include <stdio.h> 
#include <math.h>
#include <inttypes.h>

#include "jacobi.h"
#include "draw.h"
#include "get_time.h"

#define Type double


inline void swap(Type** target , Type** source) {
    Type* swap = *target;  
    *target = *source;      
    *source = swap;               
}

static void usage_msg(void) {
	fprintf(stderr, "Usage: ./jacobi <total allocated memory(KiB)>\n");
	return;
}

int main(int argc, char *argv[]){
    
    if(argc != 2 || argv == NULL) {
		usage_msg();
		return -1;
	}

    const uint64_t allocated_mem = strtoull(argv[1], NULL, 10);
    const uint32_t edge_length = sqrt(allocated_mem * 1024 / (2 * sizeof(Type)));

    const uint32_t dx = edge_length;
    const uint32_t dy = edge_length;

    const uint64_t size = dx * dy * sizeof(Type);
    Type* source = (Type*)_mm_malloc(size, 64);
    Type* target = (Type*)_mm_malloc(size, 64);

    //init
    memset(source, 0, size);
    memset(target, 0, size);

    // set top to 1
    for(uint32_t i = 0; i < dx; i++){
        source[i] = 1.0;
        target[i] = 1.0;
    }

    //set left to 1
    for(uint32_t j = 0; j < dy; j++){
        source[j * dx] = 1.0;
        target[j * dx] = 1.0;
    }

    uint64_t minimal_runtime_ms = 1000u;
    uint64_t actual_runtime_us = 0u;
    uint64_t ts = 0u;


    for(ts = 1u; actual_runtime_us < minimal_runtime_ms * 1000; ts = ts << 1u) {
        uint64_t start = get_time_micros();
        for(uint32_t t = 0; t < ts; t++){
            jacobi(source, target, dx, dy);
            swap(&target, &source);
        }
        uint64_t stop = get_time_micros();
        actual_runtime_us = stop - start;
    }

    ts = ts >> 1u;

    // draw_grid(source, dx, dy, "./data.ppm");

    double mega_updates_per_sec = dx * dy * ts * 1e-6 /((double)actual_runtime_us * 1e-6); 

    // The ouput format:
	// 	1. uint64_t allocate memory in KiB
	// 	2. double   number of mega updates per second
	// 	3. uint64_t actual runtime in milliseconds
	// 	4. uint64_t minimal runtime in milliseconds
    fprintf(stdout, "%" PRIu64 ",%lf,%" PRIu64 ",%" PRIu64 "\n", allocated_mem, mega_updates_per_sec, actual_runtime_us/1000, minimal_runtime_ms);

    _mm_free(source);
    _mm_free(target);
    
    return 0;
}


