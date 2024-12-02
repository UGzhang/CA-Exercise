#ifndef JACOBI_H
#define JACOBI_H

#include <stdint.h>
#include <likwid-marker.h>

/* This function iterates over a grid to perform a jacobi time step.
 */
void jacobi(const double * restrict grid_source, double * restrict grid_target, int32_t x, int32_t y);

#endif
