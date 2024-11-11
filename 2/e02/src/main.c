#include "jacobi.h"
#include <immintrin.h>
#define Type double

#define P(i, j)   p[(j) * (imax + 2) + (i)]

int main(int argc, char *argv[]){
    
    const uint32_t x = atoi(argv[1]);
    const uint32_t y = atoi(argv[2]);
    const uint32_t ts = atoi(argv[3]);

    const uint64_t size = x * y * sizeof(Type)
    Type* source = (Type*)_mm_malloc(size, 64);
    Type* target = (Type*)_mm_malloc(size, 64);

    //init
    memset(source, 0, size);
    memset(target, 0, size);
    for(uint32_t i = 0; i < x; i++){

    }

    uint64_t start = get_time_micros();

    for(uint32_t t = 0; t < ts; t++){
        jacobi(const double * restrict grid_source, double * restrict grid_target, uint32_t x, uint32_t y);
    }

    
    uint64_t end = get_time_micros();
    
    _mm_free() 
    _mm_free() 
    return 0;
}


