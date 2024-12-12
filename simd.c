/*
 * simd.c
 * Simple demonstration of SIMD vectorization with Matrix Multiplication.
 * The program times the matrix multiplication w/ no optimization
 * Then, another subroutine for matrix multiplication w/ SIMD vectorization.
 *
 * Chirag Dhamange
 *
 * Referenced from: https://people.freebsd.org/~lstewart/articles/cpumemory.pdf
 *
 * Updated: 11 December, 2024
 */

#include <stdlib.h>
#include <stdio.h>
#include <xmmintrin.h>
#include "timer.h"

/*******************************************************
 * Macros
 *******************************************************/

#define N (1000U)
#define SM (CLS / sizeof (double))

/******************************************************
 * Declare Matrices
 ******************************************************/

double res[N][N] __attribute__ ((aligned (64)));
double mul1[N][N] __attribute__ ((aligned (64)));
double mul2[N][N] __attribute__ ((aligned (64)));

int main (void)
{
  printf("Cache Line size:%d\n%ld\n", CLS, SM);

	double start, end;

	GET_TIME(start);
  for(unsigned int i = 0; i < N; i++)
    for(unsigned int j = 0; j < N; j++)
      mul1[i][j] = 1;

  GET_TIME(end);
  printf("Intialized Matrix A\nTime taken = %e seconds\n",
			(end - start));

  GET_TIME(start);
  for(unsigned int i = 0; i < N; i++)
    for(unsigned int j = 0; j < N; j++)
      mul2[i][j] = 1;
  GET_TIME(end);
  printf("\nIntialized Matrix B\nTime taken = %e seconds\n",
      (end - start));

  int i, i2, j, j2, k, k2;

  // Matrix Multiplication without any SIMD optimization
  GET_TIME(start);
  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
    {
      res[i][j] = 0;
      for(k = 0; k < N; k++)
        res[i][j] += mul1[i][k] * mul2[k][j];
    }
  GET_TIME(end);
  printf("\nNo Optimization\nMatrix A * Matrix B\nTime taken = %e seconds\n",
      (end - start));

  double *rres;
  double *rmul1;
  double *rmul2;

  for(i = 0; i < N; i++)
    for(j = 0; j < N; j++)
      res[i][j] = 0;
 
  // Matrix Multiplication with SIMD optimization
  // Multiply, add, and store SM values at a time
  GET_TIME(start);
  for (i = 0; i < N; i += SM)
    for (j = 0; j < N; j += SM)
      for (k = 0; k < N; k += SM)
        for (i2 = 0, rres = &res[i][j], rmul1 = &mul1[i][k];
            i2 < SM;
            ++i2, rres += N, rmul1 += N)
        {
          // load one line of cache
          _mm_prefetch (&rmul1[8], _MM_HINT_NTA);
          for (k2 = 0, rmul2 = &mul2[k][j]; k2 < SM; ++k2, rmul2 += N)
          {
            // load two double values and set upper value as 0	
            __m128d m1d = _mm_load_sd (&rmul1[k2]);
            // save same values in both registers, return the stored value
            m1d = _mm_unpacklo_pd (m1d, m1d);
            for (j2 = 0; j2 < SM; j2 += 2)
            {
              // load two double values
              __m128d m2 = _mm_load_pd (&rmul2[j2]);
              // load two double values
              __m128d r2 = _mm_load_pd (&rres[j2]);
              //store the result
              _mm_store_pd (&rres[j2],
              // multiply and add
                  _mm_add_pd (_mm_mul_pd (m2, m1d), r2));
            }
          }
        }
  GET_TIME(end);
  printf("\nSIMD Vectorization\nMatrix A * Matrix B\nTime taken = %e seconds\n",
        (end - start));

  printf("%f\n", res[0][0]);

  return 0;
}
