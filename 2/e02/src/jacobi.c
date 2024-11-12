#define _POSIX_C_SOURCE 199309L
#include "jacobi.h"

#define Type double

#define grid_source(i,j)   grid_source[i + (j) * x]
#define grid_target(i,j)   grid_target[i + (j) * x]


void jacobi(const double * restrict grid_source, double * restrict grid_target, uint32_t x, uint32_t y) {
	
	for(uint32_t j = 1; j < y-1; j++){
		for(uint32_t i = 1; i < x-1; i++){
			grid_target(i,j) = 0.25 * (grid_source(i-1,j)+grid_source(i+1,j)+grid_source(i,j-1)+grid_source(i,j+1));
		}
	}


}
