# Coordinate transformations
transform.h lib contains functions for rotation and translation of packed points and packed segments.

`void TranslateF<size>_<implementation>(PackedPoint* p, Point delta)`

size (32 or 64) --- size of floating-point numbers in bits

| \<Implementation\> | Definition       |
|--------------------|:-----------------|
| asm                | Func in assembly |
| cell 21            | cell 22          |