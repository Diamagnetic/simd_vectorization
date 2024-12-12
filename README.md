# SIMD Vectorization
Demonstration of speed-up using SIMD vectorization in C compiled using GCC compiler flags and Intel SIMD Intrinsics. The program performs two types of matrix multiplications - 1. using No optimization, 2. using Intel SIMD Intrinsics.


## How to use?
Works best on Unix-like systems. Have a GCC compiler installed and an Intel Processor.

To test the speed-up:
 * Compile the program with O3 flag or above (max O4) and msse3 flag to compile with optimize with SIMD vectorization options turned on.
```bash
$ gcc -O3 -msse3 -DCLS=$(getconf LEVEL1_DCACHE_LINESIZE) -o simd simd.c
```
 * Run the binary and timings will be shown.
```bash
$ ./simd
```
