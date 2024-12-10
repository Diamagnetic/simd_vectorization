/*
 * Chirag Dhamange
 * Math 608 Presentation Fall '24
 * vectorize.c
 * Updated - 12 December, 2024
 *
 * Simple demonstration showing the speed-up using SIMD operations
 * using simple GCC compiler flags. The program creates two large
 * arrays, and sums the result in a third array.
 * 
 * Best works on Unix-like systems
 * To test the speed-up:
 * 1. Compile the program with O0 flag to compile without
 * any compiler optimizations
 * 2. Run the binary and timings will be shown
 * 3. Compile the program with O2 flag or above (max O4) to compile with
 * SIMD vectorization options turned on.
 * 4. Run the binary and timings will be shown
 */

#include <stdio.h>
#include "timer.h"

#define SIZE (100000U)

int main(int argc, char *argv[])
{
  unsigned int a[SIZE], b[SIZE], c[SIZE];

	double start, end;

	GET_TIME(start);
  for(unsigned int i = 0; i < SIZE; i++)
    a[i] = i;

  GET_TIME(end);
  printf("Intialized array A\nTime taken = %e seconds\n",
			(end - start));

  GET_TIME(start);
  for(unsigned int i = 0; i < SIZE; i++)
    b[i] = SIZE - i;
  GET_TIME(end);
  printf("\nIntialized array B\nTime taken = %e seconds\n",
      (end - start));

	GET_TIME(start);
  for(unsigned int i = 0; i < SIZE; i++)
    c[i] = a[i] + b[i];
  GET_TIME(end);
  printf("\nArray A + Array B\nTime taken = %e seconds\n",
			(end - start));

	return 0;
}
