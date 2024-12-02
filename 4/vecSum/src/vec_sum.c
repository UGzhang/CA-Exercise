#include "vec_sum.h"
#include <immintrin.h>

float vec_sum(const float * restrict array, int32_t length) {
	
	float sum = 0.f;

	int32_t remainder = length % UNROLLTYPE;
	__m256 result = _mm256_setzero_ps();
	__m256 accu;

#if UNROLLTYPE == 2
	#pragma novector
	#pragma unroll (2)
	for(int32_t i=0;i<length;i+=8){
		accu = _mm256_loadu_ps(&array[i]);
		result = _mm256_add_ps(result, accu);

	}

#elif UNROLLTYPE == 3
	#pragma novector
	#pragma unroll (3)
	for(int32_t i=0;i<length;i+=8){
		accu = _mm256_loadu_ps(&array[i]);
		result = _mm256_add_ps(result, accu);

	}

#elif UNROLLTYPE == 4
	#pragma novector
	#pragma unroll (4)
	for(int32_t i=0;i<length;i+=8){
		accu = _mm256_loadu_ps(&array[i]);
		result = _mm256_add_ps(result, accu);

	}

#elif UNROLLTYPE == 8
	#pragma novector
	#pragma unroll (8)
	for(int32_t i=0;i<length;i+=8){
		accu = _mm256_loadu_ps(&array[i]);
		result = _mm256_add_ps(result, accu);

	}

#endif

	// horizontal addition of result
 	__m256 t1 = _mm256_hadd_ps(result,result);
    __m256 t2 = _mm256_hadd_ps(t1,t1);
    __m128 t3 = _mm256_extractf128_ps(t2,1);
    __m128 t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
	sum = _mm_cvtss_f32(t4); 
	
	for (int32_t i = 0; i < remainder; i++) {
    	sum += array[length - remainder + i];
	}


	return sum;
}

