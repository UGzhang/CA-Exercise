#define _POSIX_C_SOURCE 199309L
#include "jacobi.h"

#define Type double

#define grid_source(i,j)   grid_source[i + (j) * x]
#define grid_target(i,j)   grid_target[i + (j) * x]


void jacobi(const double * restrict grid_source, double * restrict grid_target, int32_t x, int32_t y) {
	
#if UNROLLTYPE == 1
	for(int32_t j = 1; j < y-1; j++){
		#pragma nounroll
		#pragma novector
		for(int32_t i = 1; i < x-1; i++){
			grid_target(i,j) = 0.25 * (grid_source(i-1,j)+grid_source(i+1,j)+grid_source(i,j-1)+grid_source(i,j+1));
		}
	}
#elif UNROLLTYPE == 2
	for(int32_t j = 1; j < y-1; j++){
		#pragma nounroll
		#pragma novector
		for(int32_t i = 1; i < x-2; i+=2){
			grid_target(i,j) = 0.25 * (grid_source(i-1,j)+grid_source(i+1,j)+grid_source(i,j-1)+grid_source(i,j+1));
			grid_target(i+1,j) = 0.25 * (grid_source(i,j) + grid_source(i+2,j) + grid_source(i+1,j-1) + grid_source(i+1,j+1));
		}

		if (x % 2 == 1) {
			grid_target(x-2,j) = 0.25 * (grid_source(x-3,j) + grid_source(x-1,j) + grid_source(x-2,j-1) + grid_source(x-2,j+1));
		}
	}

#elif UNROLLTYPE == 4
	int32_t remainder = (x-2) % 4;
	for(int32_t j = 1; j < y-1; j++){
		#pragma nounroll
		#pragma novector		
		for(int32_t i = 1; i < x-4; i+=4){
			grid_target(i,j)    = 0.25 * (grid_source(i-1,j)  + grid_source(i+1,j)  + grid_source(i,j-1)    + grid_source(i,j+1));
			grid_target(i+1,j)  = 0.25 * (grid_source(i,j)    + grid_source(i+2,j)  + grid_source(i+1,j-1)  + grid_source(i+1,j+1));
			grid_target(i+2,j)  = 0.25 * (grid_source(i+1,j)  + grid_source(i+3,j)  + grid_source(i+2,j-1)  + grid_source(i+2,j+1));
			grid_target(i+3, j) = 0.25 * (grid_source(i+2, j) + grid_source(i+4, j) + grid_source(i+3, j-1) + grid_source(i+3, j+1));
		}

    	for (int32_t i = x - remainder; i < x-1; i++) {
        	grid_target(i,j) = 0.25 * (grid_source(i-1,j) + grid_source(i+1,j) + grid_source(i,j-1) + grid_source(i,j+1));
    	}

	}

#elif UNROLLTYPE == 8
	int32_t remainder = (x-2) % 8;
	for(int32_t j = 1; j < y-1; j++){
		#pragma nounroll
		#pragma novector		
		for(int32_t i = 1; i < x-8; i+=8){
			grid_target(i,j)    = 0.25 * (grid_source(i-1,j)  + grid_source(i+1,j)  + grid_source(i,j-1)    + grid_source(i,j+1));
			grid_target(i+1,j)  = 0.25 * (grid_source(i,j)    + grid_source(i+2,j)  + grid_source(i+1,j-1)  + grid_source(i+1,j+1));
			grid_target(i+2,j)  = 0.25 * (grid_source(i+1,j)  + grid_source(i+3,j)  + grid_source(i+2,j-1)  + grid_source(i+2,j+1));
			grid_target(i+3, j) = 0.25 * (grid_source(i+2, j) + grid_source(i+4, j) + grid_source(i+3, j-1) + grid_source(i+3, j+1));
			grid_target(i+4, j) = 0.25 * (grid_source(i+3, j) + grid_source(i+5, j) + grid_source(i+4, j-1) + grid_source(i+4, j+1));
			grid_target(i+5, j) = 0.25 * (grid_source(i+4, j) + grid_source(i+6, j) + grid_source(i+5, j-1) + grid_source(i+5, j+1));
			grid_target(i+6, j) = 0.25 * (grid_source(i+5, j) + grid_source(i+7, j) + grid_source(i+6, j-1) + grid_source(i+6, j+1));
			grid_target(i+7, j) = 0.25 * (grid_source(i+6, j) + grid_source(i+8, j) + grid_source(i+7, j-1) + grid_source(i+7, j+1));

		}

    	for (int32_t i = x - remainder; i < x-1; i++) {
        	grid_target(i,j) = 0.25 * (grid_source(i-1,j) + grid_source(i+1,j) + grid_source(i,j-1) + grid_source(i,j+1));
    	}
	}


#elif UNROLLTYPE == 16
	int32_t remainder = (x-2) % 16;
	for(int32_t j = 1; j < y-1; j++){
		#pragma nounroll
		#pragma novector		
		for(int32_t i = 1; i < x-16; i+=16){
			grid_target(i,j)    = 0.25 * (grid_source(i-1,j)  + grid_source(i+1,j)  + grid_source(i,j-1)    + grid_source(i,j+1));
			grid_target(i+1,j)  = 0.25 * (grid_source(i,j)    + grid_source(i+2,j)  + grid_source(i+1,j-1)  + grid_source(i+1,j+1));
			grid_target(i+2,j)  = 0.25 * (grid_source(i+1,j)  + grid_source(i+3,j)  + grid_source(i+2,j-1)  + grid_source(i+2,j+1));
			grid_target(i+3, j) = 0.25 * (grid_source(i+2, j) + grid_source(i+4, j) + grid_source(i+3, j-1) + grid_source(i+3, j+1));
			grid_target(i+4, j) = 0.25 * (grid_source(i+3, j) + grid_source(i+5, j) + grid_source(i+4, j-1) + grid_source(i+4, j+1));
			grid_target(i+5, j) = 0.25 * (grid_source(i+4, j) + grid_source(i+6, j) + grid_source(i+5, j-1) + grid_source(i+5, j+1));
			grid_target(i+6, j) = 0.25 * (grid_source(i+5, j) + grid_source(i+7, j) + grid_source(i+6, j-1) + grid_source(i+6, j+1));
			grid_target(i+7, j) = 0.25 * (grid_source(i+6, j) + grid_source(i+8, j) + grid_source(i+7, j-1) + grid_source(i+7, j+1));
			grid_target(i+8,j)  = 0.25 * (grid_source(i+7,j)  + grid_source(i+9,j)  + grid_source(i+8,j-1)    + grid_source(i+8,j+1));
			grid_target(i+9,j)  = 0.25 * (grid_source(i+8,j)    + grid_source(i+10,j)  + grid_source(i+9,j-1)  + grid_source(i+9,j+1));
			grid_target(i+10,j)  = 0.25 * (grid_source(i+9,j)  + grid_source(i+11,j)  + grid_source(i+10,j-1)  + grid_source(i+10,j+1));
			grid_target(i+11, j) = 0.25 * (grid_source(i+10, j) + grid_source(i+12, j) + grid_source(i+11, j-1) + grid_source(i+11, j+1));
			grid_target(i+12, j) = 0.25 * (grid_source(i+11, j) + grid_source(i+13, j) + grid_source(i+12, j-1) + grid_source(i+12, j+1));
			grid_target(i+13, j) = 0.25 * (grid_source(i+12, j) + grid_source(i+14, j) + grid_source(i+13, j-1) + grid_source(i+13, j+1));
			grid_target(i+14, j) = 0.25 * (grid_source(i+13, j) + grid_source(i+15, j) + grid_source(i+14, j-1) + grid_source(i+14, j+1));
			grid_target(i+15, j) = 0.25 * (grid_source(i+14, j) + grid_source(i+16, j) + grid_source(i+15, j-1) + grid_source(i+15, j+1));

		}

    	for (int32_t i = x - remainder; i < x-1; i++) {
        	grid_target(i,j) = 0.25 * (grid_source(i-1,j) + grid_source(i+1,j) + grid_source(i,j-1) + grid_source(i,j+1));
    	}
	}

#endif



}
