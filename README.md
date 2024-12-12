# SIMD Vectorization
Demonstration of speed-up using SIMD vectorization in C compiled using GCC compiler flags and Intel SIMD Intrinsics. The simd.c program performs two types of matrix multiplications - 1. using No optimization, 2. using Intel SIMD SSE 2 Intrinsics. Similarly, the simd\_add.c program performs vector addition.

## How to use?
Works best on Unix-like systems. Have a GCC compiler installed and an Intel Processor.

To test the speed-up:
 * Compile any of the two programs with O3 flag or above (max O4) and msse2 flag to compile with optimize with SIMD vectorization options turned on.
```bash
$ gcc -O3 -msse2 -DCLS=$(getconf LEVEL1_DCACHE_LINESIZE) -o <outfile> <filname>.c
```
 * Run the binary and timings will be shown.
```bash
$ ./outfile
```
