#ifndef JACOBI_H
#define JACOBI_H

#include <stdint.h>

/* This function iterates over a grid to perform a jacobi time step.
 */
void jacobi(const double * restrict grid_source, double * restrict grid_target, uint32_t x, uint32_t y);

#endif
