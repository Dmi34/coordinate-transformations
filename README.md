# Coordinate transformations
DoubleGeometry namespace contains functions for rotation and translation of double precision packed points and packed segments.

Most effective functions: 
- `PackedPoint Translate_imm(const PackedPoint& p, Point delta)`
- `PackedPoint Rotate_imm(const PackedPoint& p, RadianAngle angle)`
- `PackedSegment Translate_imm(const PackedSegment& s, Point delta)`
- `PackedSegment Rotate_imm(const PackedSegment& s, RadianAngle angle)`

Also lib contains benchmarks for different implementation of transformations with/without avx.