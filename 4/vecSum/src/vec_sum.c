#include "vec_sum.h"
#include <immintrin.h>

float vec_sum(const float * restrict array, int32_t length) {
	
	float sum = 0.f;

#if UNROLLTYPE == 1

	#pragma novector
	#pragma nounroll
	for(int i=0;i<length;i++){
		sum += array[i];
	}

// SSE
#elif UNROLLTYPE == 4
	
	int32_t remainder = length % UNROLLTYPE;
	__m128 result = _mm_setzero_ps();
	__m128 accu;

	#pragma nounroll
	#pragma novector
	for(int32_t i=0;i<length - remainder;i+=UNROLLTYPE){
		accu = _mm_loadu_ps(&array[i]);
		result = _mm_add_ps(result, accu);
	}

	// horizontal addition of result
	__m128 shuf = _mm_movehdup_ps(result);       
    __m128 sums = _mm_add_ps(result, shuf);
    shuf = _mm_movehl_ps(shuf, sums); 
    sums = _mm_add_ss(sums, shuf);
	sum = _mm_cvtss_f32(sums);

	for (int32_t i = 0; i < remainder; i++) {
    	sum += array[length - remainder + i];
	}
	
// AVX
#elif UNROLLTYPE == 8

	int32_t remainder = length % UNROLLTYPE;
	__m256 result = _mm256_setzero_ps();
	__m256 accu;

	#pragma nounroll
	#pragma novector
	for(int32_t i=0;i<length - remainder;i+=UNROLLTYPE){
		accu = _mm256_loadu_ps(&array[i]);
		result = _mm256_add_ps(result, accu);

	}

	// horizontal addition of result
 	__m256 t1 = _mm256_hadd_ps(result,result);
    __m256 t2 = _mm256_hadd_ps(t1,t1);
    __m128 t3 = _mm256_extractf128_ps(t2,1);
    __m128 t4 = _mm_add_ss(_mm256_castps256_ps128(t2),t3);
	sum = _mm_cvtss_f32(t4);  
	
	for (int32_t i = 0; i < remainder; i++) {
    	sum += array[length - remainder + i];
	}



// AVX512
#elif UNROLLTYPE == 16
	int32_t remainder = length % UNROLLTYPE;
	__m512 result = _mm512_setzero_ps();
	__m512 accu;

	#pragma nounroll
	#pragma novector
	for(int32_t i=0;i<length - remainder;i+=UNROLLTYPE){
		accu = _mm512_loadu_ps(&array[i]);
		result = _mm512_add_ps(result, accu);
	}

	// horizontal addition of result
	__m512 tmp = _mm512_add_ps(result,_mm512_shuffle_f32x4(result,result,_MM_SHUFFLE(0,0,3,2)));
    __m128 r = _mm512_castps512_ps128(_mm512_add_ps(tmp,_mm512_shuffle_f32x4(tmp,tmp,_MM_SHUFFLE(0,0,0,1))));
    r = _mm_hadd_ps(r,r);
    sum = _mm_cvtss_f32(_mm_hadd_ps(r,r));


	for (int32_t i = 0; i < remainder; i++) {
    	sum += array[length - remainder + i];
	}
#endif

	return sum;
}

