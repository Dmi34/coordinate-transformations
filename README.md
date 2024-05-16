# Coordinate transformations

The project implements functions for time-efficient translation and rotation of geomentric points and segments on a plane. SIMD instructions and AVX2 technologies are used for further optimization. Different implementations of translating and rotating functions are compared in terms of time-efficiency. The project uses Bazel building system.

The lib folder contains transform.h header, where the following methods are implemented: 

- `PackedPoint TranslateImm(const PackedPoint& p, Point delta)`
- `PackedPoint RotateImm(const PackedPoint& p, RadianAngle angle)`
- `PackedSegment TranslateImm(const PackedSegment& s, Point delta)`
- `PackedSegment RotateImm(const PackedSegment& s, RadianAngle angle)`

They are implemented on C++ via compiler intrinsics. lib folder contains benchmarks for them.

The testing folder contains transform.h header, where different implementations of translating and rotating methods are located. Every method from lib folder is present in testing, in addition testing contains methods on C++ implemented without compiler intrinsics:

- `PackedPoint TranslateCpp(const PackedPoint& p, Point delta)`
- `PackedPoint RotateCpp(const PackedPoint& p, RadianAngle angle)`
- `PackedSegment TranslateCpp(const PackedSegment& s, Point delta)`
- `PackedSegment RotateCpp(const PackedSegment& s, RadianAngle angle)`

Methods with the same interface that call assembly functions and serve as wrappers for them:

- `PackedPoint TranslateAsm(const PackedPoint& p, Point delta)`
- `PackedPoint RotateAsm(const PackedPoint& p, RadianAngle angle)`
- `PackedSegment TranslateAsm(const PackedSegment& s, Point delta)`
- `PackedSegment RotateAsm(const PackedSegment& s, RadianAngle angle)`

Methods implemented on Intel Assembly. Implementation of each method is located in its .asm file and each method is declared in the header using extern "C" key word. 

In each header two namespaces are present: SingleGeomentry (contains methods and data structures for processing single precision points), DoubleGeomentry (contains methods and data structures for processing double precision points). 

Benchmarks and tests for both SingleGeometry and DoubleGeomentry are located in testing folder. 

# Installation and usage

The project uses Bazel building system. The project has a dependency on [Catch2 library](https://github.com/catchorg/Catch2) (used for testing and benchmarking).

# Perforamnce

Performance was measured using Catch2 benchmarks, with gcc 11.4.0 compiler (O0 level of optimization). Turning on higher levels of optimization causes the compiler to utilize intrinsics itself.

For DoubleGeomentry:

| Method name              | Mean time (for points) | Mean time (for segments) |
| :---                     |         :----:         |   ---:                   |
| TranslateDoublePointAsm  | 6.106  ns              | -                        |
| TranslateDoubleSegmentAsm| -                      | 11.8328 ns               |
| TranslateAsm             | 15.913 ns              | 15.0715 ns               |
| TranslateImm             | 18.585 ns              | 23.0546 ns               |
| TranslateCpp             | 29.380 ns              | 55.9693 ns               |
| :---                     |         :----:         |  ---:                    |
| RotateDoublePointAsm     | 6.968  ns              |  -                       |
| RotateDoubleSegmentAsm    | -                      | 11.9385 ns               |
| RotateAsm                | 31.945 ns              | 28.6761 ns               |
| RotateImm                | 42.069 ns              | 49.5887 ns               |
| RotateCpp                | 53.109 ns              | 95.9351 ns               |


For SingleGeomentry:

| Method name              | Mean time (for points) | Mean time (for segments) |
| :---                     |         :----:         |   ---:                   |
| TranslateSinglePointAsm  | 6.106  ns              | -                        |
| TranslateSingleSegmentAsm| -                      | 11.8328 ns               |
| TranslateAsm             | 15.913 ns              | 15.0715 ns               |
| TranslateImm             | 18.585 ns              | 23.0546 ns               |
| TranslateCpp             | 29.380 ns              | 55.9693 ns               |
| :---                     |         :----:         |  ---:                    |
| RotateSinglePointAsm     | 6.968  ns              |  -                       |
| RotateSingleSegmentAsm   | -                      | 11.9385 ns               |
| RotateAsm                | 31.945 ns              | 28.6761 ns               |
| RotateImm                | 42.069 ns              | 49.5887 ns               |
| RotateCpp                | 53.109 ns              | 95.9351 ns               |

# Contributions

Prod. by Mikhail Klimov (github: KlimovMikh) and Dmitry Antashkevish (github: Dmi34)

