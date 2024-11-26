#define _POSIX_C_SOURCE 199309L
#include "jacobi.h"
#include <immintrin.h>
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

//SSE
#elif UNROLLTYPE == 2
	int32_t remainder = (x-2) % UNROLLTYPE;
	__m128d accu[4];
	__m128d tmp[2];
	__m128d result;
	const __m128d factor = _mm_set_pd(0.25,0.25);

	for(int32_t j = 1; j < y-1; j++){
		#pragma nounroll
		#pragma novector		
		for(int32_t i = 1; i < x-1-remainder; i+=UNROLLTYPE){

			accu[0] = _mm_loadu_pd(&grid_source(i-1,j));
			accu[1] = _mm_loadu_pd(&grid_source(i+1,j));
			accu[2] = _mm_loadu_pd(&grid_source(i,j+1));
			accu[3] = _mm_loadu_pd(&grid_source(i,j-1));

			tmp[0] = _mm_add_pd(accu[0], accu[1]);
			tmp[1] = _mm_add_pd(accu[2], accu[3]);
			result = _mm_add_pd(tmp[0], tmp[1]);

			result = _mm_mul_pd(result, factor);
			_mm_storeu_pd(&grid_target(i,j), result);

		}

    	for (int32_t i = x-remainder-1; i < x-1; i++) {
        	grid_target(i,j) = 0.25 * (grid_source(i-1,j) + grid_source(i+1,j) + grid_source(i,j-1) + grid_source(i,j+1));
    	}

	}

//AVX
#elif UNROLLTYPE == 4
	int32_t remainder = (x-2) % UNROLLTYPE;
	__m256d accu[4];
	__m256d tmp[2];
	__m256d result;
	const __m256d factor = _mm256_set_pd(0.25,0.25,0.25,0.25);

	for(int32_t j = 1; j < y-1; j++){
		#pragma nounroll
		#pragma novector		
		for(int32_t i = 1; i < x-1-remainder; i+=UNROLLTYPE){

			accu[0] = _mm256_loadu_pd(&grid_source(i-1,j));
			accu[1] = _mm256_loadu_pd(&grid_source(i+1,j));
			accu[2] = _mm256_loadu_pd(&grid_source(i,j+1));
			accu[3] = _mm256_loadu_pd(&grid_source(i,j-1));

			tmp[0] = _mm256_add_pd(accu[0], accu[1]);
			tmp[1] = _mm256_add_pd(accu[2], accu[3]);
			result = _mm256_add_pd(tmp[0], tmp[1]);

			result = _mm256_mul_pd(result, factor);
			_mm256_storeu_pd(&grid_target(i,j), result);

		}

    	for (int32_t i = x-remainder-1; i < x-1; i++) {
        	grid_target(i,j) = 0.25 * (grid_source(i-1,j) + grid_source(i+1,j) + grid_source(i,j-1) + grid_source(i,j+1));
    	}

	}

//AVX512
#elif UNROLLTYPE == 8
	int32_t remainder = (x-2) % UNROLLTYPE;
	__m512d accu[4];
	__m512d tmp[2];
	__m512d result;
	const __m512d factor = _mm512_set_pd(0.25,0.25,0.25,0.25,0.25,0.25,0.25,0.25);

	for(int32_t j = 1; j < y-1; j++){
		#pragma nounroll
		#pragma novector		
		for(int32_t i = 1; i < x-1-remainder; i+=UNROLLTYPE){

			accu[0] = _mm512_loadu_pd(&grid_source(i-1,j));
			accu[1] = _mm512_loadu_pd(&grid_source(i+1,j));
			accu[2] = _mm512_loadu_pd(&grid_source(i,j+1));
			accu[3] = _mm512_loadu_pd(&grid_source(i,j-1));

			tmp[0] = _mm512_add_pd(accu[0], accu[1]);
			tmp[1] = _mm512_add_pd(accu[2], accu[3]);
			result = _mm512_add_pd(tmp[0], tmp[1]);

			result = _mm512_mul_pd(result, factor);
			_mm512_storeu_pd(&grid_target(i,j), result);

		}

    	for (int32_t i = x-remainder-1; i < x-1; i++) {
        	grid_target(i,j) = 0.25 * (grid_source(i-1,j) + grid_source(i+1,j) + grid_source(i,j-1) + grid_source(i,j+1));
    	}

	}
#endif



}
