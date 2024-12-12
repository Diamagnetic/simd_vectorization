/*
 * simd_add.c
 * Simple demonstration of SIMD vectorization with Vector addition using Intel SSE C intrinsics.
 * The program times the addition of two vector w/ and w/o SIMD vectorization optimization
 *
 * Chirag Dhamange
 *
 * Updated: 12 December, 2024
 */

#include <stdlib.h>
#include <stdio.h>
#include <emmintrin.h>
#include "timer.h"

/******************************************************
 * Macros
 *******************************************************/

#define N (10000000U)
#define SM (CLS / sizeof (double))
// max vector register size = 128
#define STRIDE (128 / sizeof(unsigned int))

/******************************************************
 * Declare Matrices
 ******************************************************/

unsigned int res[N] __attribute__ ((aligned (CLS)));
unsigned int a[N] __attribute__ ((aligned (CLS)));
unsigned int b[N] __attribute__ ((aligned (CLS)));

int main (void)
{
  printf("Cache Line size:%d\n%ld\n", CLS, SM);

  double start, end;

  GET_TIME(start);
  for(unsigned int i = 0; i < N; i++)
      a[i] = 1;
  GET_TIME(end);
  printf("Intialized array A\nTime taken = %15.14f seconds\n",
        (end - start));

  GET_TIME(start);
  for(unsigned int i = 0; i < N; i++)
      b[i] = 1;
  GET_TIME(end);
  printf("\nIntialized array B\nTime taken = %15.14f seconds\n",
      (end - start));

  // Vector addition without any SIMD optimization
  GET_TIME(start);
  for(unsigned int i = 0; i < N; i++)
      res[i] = a[i] + b[i];
	GET_TIME(end);
  printf("\nNo Optimization\nArray A + Array B\nTime taken = %15.14f seconds\n",
      (end - start));

  unsigned int *rres;
  unsigned int *ra;
  unsigned int *rb;

  for(unsigned int i = 0; i < N; i++)
      res[i] = 0;

  unsigned int i;
  unsigned short int i2;
  // Matrix Multiplication with SIMD optimization
  // Multiply, add, and store SM values at a time
  GET_TIME(start);
  for (i = 0, ra = &a[i]; i < N; i += SM, ra += SM)
  {
    _mm_prefetch(&ra[SM], _MM_HINT_NTA);
    for(rres = &res[i], rb = &b[i], i2 = 0;
        i2 < SM;
        i2 += STRIDE, rres += STRIDE)
    {
      // Load 4 32-bit integers into a 128-bit vector register for each of the two arrays
      __m128i ma = _mm_set_epi32(ra[i2], ra[i2 + 1], ra[i2 + 2], ra[i2 + 3]);
      __m128i mb = _mm_set_epi32(rb[i2], rb[i2 + 1], rb[i2 + 2], rb[i2 + 3]);

      // add and store the result of the vector addition
      _mm_store_si128((__m128i*)&rres[i2],
        _mm_add_epi32(ma, mb)
      );
    }
  }

  GET_TIME(end);
  printf("\nSIMD Vectorization\nArray A + Array B\nTime taken = %15.14f seconds\n",
        (end - start));

  // Simple verification to check whether all values
  // resulting from the SIMD operation are as expected
  for(unsigned int i = 0; i < N; i++)
    if(res[2] != 2)
    {
      printf("False\n");
			return -1;
    }

  printf("All values correct\n");

  return 0;
}
