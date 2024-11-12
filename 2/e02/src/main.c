#include <immintrin.h>
#include <string.h>
#include <stdio.h> 

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
	fprintf(stderr, "Usage: ./jacobi <dx> <dy> <timestep>\n");
	return;
}

int main(int argc, char *argv[]){
    
    if(argc != 4 || argv == NULL) {
		usage_msg();
		return -1;
	}

    const uint32_t dx = atoi(argv[1]);
    const uint32_t dy = atoi(argv[2]);
    const uint32_t ts = atoi(argv[3]);

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


    uint64_t start = get_time_micros();

    for(uint32_t t = 0; t < ts; t++){
        jacobi(source, target, dx, dy);
        swap(&target, &source);

    }
    uint64_t stop = get_time_micros();

    uint64_t runtime_ms = (stop - start) / 1000;

    // for(uint32_t j = 0; j < dy; j++){
	// 	for(uint32_t i = 0; i < dx; i++){
    //         printf("%lf ", target[i + j * dx]);
    //     }
    //     printf("\n");
    // }

    draw_grid(source, dx, dy, "./data.ppm");
    
    _mm_free(source);
    _mm_free(target);

    printf("runtime: %lu\n", runtime_ms);
    return 0;
}


