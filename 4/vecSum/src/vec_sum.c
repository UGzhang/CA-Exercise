#include "vec_sum.h"

float vec_sum(const float * restrict array, int32_t length) {
	
	float sum_all = 0.0f;

#if UNROLLTYPE == 1
	float sum = 0.0f;
	#pragma novector
	#pragma nounroll
	for(int i=0;i<length;i++){
		sum += array[i];
	}
	sum_all = sum;

#elif UNROLLTYPE == 2
	float sum[]={0.0f,0.0f};
	int32_t remainder = length % 2;
	#pragma nounroll
	#pragma novector
	for(int32_t i=0;i<length- remainder; i+=2){
		sum[0] += array[i];
		sum[1] += array[i+1];
	}
	sum[0] += sum[1];
	if(remainder) sum[0] += array[length-1];
	sum_all = sum[0];

#elif UNROLLTYPE == 3
	float sum[]={0.0f,0.0f,0.0f};
	int32_t remainder = length % 3;
	#pragma nounroll
	#pragma novector
	for(int32_t i=0;i<length - remainder;i+=3){
		sum[0] += array[i];
		sum[1] += array[i+1];
		sum[2] += array[i+2];
	}
	sum_all = sum[0] + sum[1] + sum[2];
	for (int32_t i = 0; i < remainder; i++) {
    	sum_all += array[length - remainder + i];
	}

#elif UNROLLTYPE == 4
	float sum[]={0.0f,0.0f,0.0f, 0.0f};
	int32_t remainder = length % 4;
	#pragma nounroll
	#pragma novector
	for(int32_t i=0;i<length - remainder;i+=4){
		sum[0] += array[i];
		sum[1] += array[i+1];
		sum[2] += array[i+2];
		sum[3] += array[i+3];
	}
	sum_all = sum[0] + sum[1] + sum[2] + sum[3];
	for (int32_t i = 0; i < remainder; i++) {
    	sum_all += array[length - remainder + i];
	}
	

#elif UNROLLTYPE == 8
	float sum[UNROLLTYPE] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
	int32_t remainder = length % UNROLLTYPE;
	#pragma nounroll
	#pragma novector
	for(int32_t i=0;i<length - remainder;i+=UNROLLTYPE){
		sum[0] += array[i];
		sum[1] += array[i+1];
		sum[2] += array[i+2];
		sum[3] += array[i+3];
		sum[4] += array[i+4];
		sum[5] += array[i+5];
		sum[6] += array[i+6];
		sum[7] += array[i+7];
	}
	for(int i=0;i<UNROLLTYPE;i++){
		sum_all+=sum[i];
	}
	for (int32_t i = 0; i < remainder; i++) {
    	sum_all += array[length - remainder + i];
	}


#elif UNROLLTYPE == 16
	float sum[UNROLLTYPE] = {0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f,0.0f};
	int32_t remainder = length % UNROLLTYPE;
	#pragma nounroll
	#pragma novector
	for(int32_t i=0;i<length - remainder;i+=UNROLLTYPE){
		sum[0] += array[i];
		sum[1] += array[i+1];
		sum[2] += array[i+2];
		sum[3] += array[i+3];
		sum[4] += array[i+4];
		sum[5] += array[i+5];
		sum[6] += array[i+6];
		sum[7] += array[i+7];
		sum[8] += array[i+8];
		sum[9] += array[i+9];
		sum[10] += array[i+10];
		sum[11] += array[i+11];
		sum[12] += array[i+12];
		sum[13] += array[i+13];
		sum[14] += array[i+14];
		sum[15] += array[i+15];
	}
	for(int i=0;i<UNROLLTYPE;i++){
		sum_all+=sum[i];
	}
	for (int32_t i = 0; i < remainder; i++) {
    	sum_all += array[length - remainder + i];
	}
#endif

	return sum_all;
}

