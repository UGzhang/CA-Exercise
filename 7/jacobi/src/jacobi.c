#define _POSIX_C_SOURCE 199309L
#include "jacobi.h"
#include <immintrin.h>
#define Type double

#define grid_source(i,j)   grid_source[i + (j) * x]
#define grid_target(i,j)   grid_target[i + (j) * x]

void jacobi(const double * restrict grid_source, double * restrict grid_target, int32_t x, int32_t y) {
	
#ifdef Bx
#ifdef By
	__m256d accu[4],res,tmp1,tmp2;
	uint32_t num_block_x = (x-1-1)/Bx;
	uint32_t num_block_y = y/By;
	uint32_t block_start_x = 1;
	uint32_t block_start_y = 1;
	uint32_t block_end_y=By,block_end_x=Bx+1;
	uint32_t last_blk_remainder_x = ((x-1-1)%Bx)%4;

	if(num_block_y==0){
		block_end_y = y-1;
		num_block_y = 1;
	}else if(y==By){
		block_end_y = y-1;
	}else if(y%By!=0){
		num_block_y++;
	}

	for(uint32_t by=0;by<num_block_y;by++){
		block_start_x=1;
		for(uint32_t bx=0;bx<num_block_x;bx++){
			block_end_x = block_start_x+Bx;
			for(uint32_t i=block_start_y;i<block_end_y;i++){ //for the row (along y)
				#pragma novector
				#pragma nounroll
				for(uint32_t j=block_start_x;j<block_end_x;j+=4){
					accu[0] = _mm256_loadu_pd(&grid_source[(i-1)*x+j]);//bottom
					accu[1] = _mm256_loadu_pd(&grid_source[i*x+j+1]);//right
					accu[2] = _mm256_loadu_pd(&grid_source[i*x+j-1]);//left
					accu[3] = _mm256_loadu_pd(&grid_source[(i+1)*x+j]);//top

					tmp1=_mm256_add_pd(accu[0],accu[1]);
					tmp2=_mm256_add_pd(accu[2],accu[3]);
					res=_mm256_add_pd(tmp1,tmp2);
					res=_mm256_mul_pd(res,_mm256_set1_pd(0.25));
					_mm256_storeu_pd(&grid_target[i*x+j],res);
				}
			}
			block_start_x = block_end_x;
		}
		//last block along x
		block_end_x = x-1;
		for(uint32_t i=block_start_y;i<block_end_y;i++){ //for the row (along y)
			#pragma novector
			#pragma nounroll
			for(uint32_t j=block_start_x;j<x-4-last_blk_remainder_x;j+=4){
				accu[0] = _mm256_loadu_pd(&grid_source[(i-1)*x+j]);//bottom
				accu[1] = _mm256_loadu_pd(&grid_source[i*x+j+1]);//right
				accu[2] = _mm256_loadu_pd(&grid_source[i*x+j-1]);//left
				accu[3] = _mm256_loadu_pd(&grid_source[(i+1)*x+j]);//top

				tmp1=_mm256_add_pd(accu[0],accu[1]);
				tmp2=_mm256_add_pd(accu[2],accu[3]);
				res=_mm256_add_pd(tmp1,tmp2);
				res=_mm256_mul_pd(res,_mm256_set1_pd(0.25));
				_mm256_storeu_pd(&grid_target[i*x+j],res);
			}
			for(uint32_t k=last_blk_remainder_x;k>0;k--){
				grid_target[i*x+(x-1-k)] = (grid_source[(i-1)*x+(x-1-k)]
									+ grid_source[i*x+(x-1-k)+1]
									+ grid_source[i*x+(x-1-k)-1]
									+ grid_source[(i+1)*x+(x-1-k)])*0.25;
			}
		}

		block_start_y = block_end_y;
		if(by == num_block_y-2){
			block_end_y = y-1;
		}else{
			block_end_y = block_start_y+By;
		}
	}
#endif
#endif

}
