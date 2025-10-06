;------------------------------------------------------------------------------
; void RotateSinglePointAsm(const PackedPoint* dest, const PackedPoint& p, Direction dir);
;------------------------------------------------------------------------------
        section .text

        global RotateSinglePointAsm
        global RotateSingleSegmentAsm

RotateSinglePointAsm:

        vbroadcastss ymm1, xmm0 ; ymm1 = cos
        pshufd xmm0, xmm0, 0x55
        vbroadcastss ymm0, xmm0 ; ymm0 = sin
        vmulps ymm2, ymm1, [rsi] ; ymm2 = x*cos
        vmulps ymm3, ymm0, [rsi] ; ymm3 = x*sin
        vmovaps ymm4, [rsi + 32] ; ymm4 = y
        vfnmadd231ps ymm2, ymm4, ymm0 ; ymm2 = -y*sin + x*cos
        vfmadd231ps ymm3, ymm4, ymm1 ; ymm3 = y*cos + x*sin
        vmovaps [rdi], ymm2
        vmovaps [rdi + 32], ymm3
        ret

;--------------------------------------------------------------------------------------------------
; void RotateSingleSegmentAsm(const PackedSegment* dest, const PackedSegment& s, Direction dir);
;--------------------------------------------------------------------------------------------------

RotateSingleSegmentAsm:
        vbroadcastss ymm1, xmm0 ; ymm1 = cos
        pshufd xmm0, xmm0, 0x55
        vbroadcastss ymm0, xmm0 ; ymm0 = sin
        vmulps ymm2, ymm1, [rsi] ; ymm2 = x1*cos
        vmulps ymm3, ymm0, [rsi] ; ymm3 = x1*sin
        vmulps ymm4, ymm1, [rsi + 64] ; ymm4 = x2*cos
        vmulps ymm5, ymm0, [rsi + 64] ; ymm5 = x2*sin
        vmovaps ymm6, [rsi + 32] ; ymm6 = y1
        vmovaps ymm7, [rsi + 96] ; ymm7 = y2
        vfnmadd231ps ymm2, ymm6, ymm0 ; ymm2 = -y1*sin + x1*cos
        vfmadd231ps ymm3, ymm6, ymm1 ; ymm3 = y1*cos + x1*sin
        vfnmadd231ps ymm4, ymm7, ymm0 ; ymm2 = -y2*sin + x2*cos
        vfmadd231ps ymm5, ymm7, ymm1 ; ymm3 = y2*cos + x2*sin
        vmovaps [rdi], ymm2
        vmovaps [rdi + 32], ymm3
        vmovaps [rdi + 64], ymm4
        vmovaps [rdi + 96], ymm5
        ret
