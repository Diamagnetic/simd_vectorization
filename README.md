# SIMD Vectorization
Demonstration of speed-up using SIMD vectorization in C compiled using GCC compiler flags. The program creates two large arrays, and sums the result in a third array.


## How to use?
Best works on Unix-like systems. Have a GCC compiler installed.

To test the speed-up:
 * Compile the program with O1 flag to compile without
 * any optimizations
```bash
$ gcc -O0 -o vectorize vectorize.c
```
 * Run the binary and timings will be shown for 3 section - creating the two arrays, and addition of the two arrays and storing in another array.
```bash
$ ./vectorize
```
 * Compile the program with O2 flag or above (max O4) to compile with SIMD vectorization options turned on.
```bash
$ gcc -O2 -o vectorize vectorize.c
```
 * Run the binary and timings will be shown.
```bash
$ ./vectorize
```
