#include "vec_sum.h"

float vec_sum(const float * restrict array, int32_t length) {
	float sum=0.f;
	for(int i=0;i<length;i++){
		sum += array[i];
	}
	return sum;
}

