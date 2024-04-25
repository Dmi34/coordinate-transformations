;------------------------------------------------------------------------------
; void Rotate_asm(const PackedPoint* target, const PackedPoint& p, DoubleDirection dir);
;------------------------------------------------------------------------------
        section .text

        global RotatePoint_asm
        global RotateSegment_asm

RotatePoint_asm:
        vbroadcastsd ymm0, xmm0
        vbroadcastsd ymm1, xmm1
        vmulpd ymm2, ymm0, [rsi] ; ymm2 = x*cos
        vmulpd ymm3, ymm1, [rsi] ; ymm3 = x*sin
        vmovapd ymm4, [rsi + 32] ; ymm4 = y
        vfnmadd231pd ymm2, ymm4, ymm1 ; ymm2 = -y*sin + x*cos
        vfmadd231pd ymm3, ymm4, ymm0 ; ymm3 = y*cos + x*sin
        vmovapd [rdi], ymm2
        vmovapd [rdi + 32], ymm3
        ret

;--------------------------------------------------------------------------------------------------
;void RotateSegment_asm(const PackedSegment* target, const PackedSegment& p, DoubleDirection dir);
;--------------------------------------------------------------------------------------------------

RotateSegment_asm:
        vbroadcastsd ymm0, xmm0
        vbroadcastsd ymm1, xmm1
        vmulpd ymm2, ymm0, [rsi] ; ymm2 = x1*cos
        vmulpd ymm3, ymm1, [rsi] ; ymm3 = x1*sin
        vmulpd ymm4, ymm0, [rsi + 64] ; ymm4 = x2*cos
        vmulpd ymm5, ymm1, [rsi + 64] ; ymm5 = x2*sin
        vmovapd ymm6, [rsi + 32] ; ymm6 = y1
        vmovapd ymm7, [rsi + 96] ; ymm7 = y2
        vfnmadd231pd ymm2, ymm6, ymm1 ; ymm2 = -y1*sin + x1*cos
        vfmadd231pd ymm3, ymm6, ymm0 ; ymm3 = y1*cos + x1*sin
        vfnmadd231pd ymm4, ymm7, ymm1 ; ymm2 = -y2*sin + x2*cos
        vfmadd231pd ymm5, ymm7, ymm0 ; ymm3 = y2*cos + x2*sin
        vmovapd [rdi], ymm2
        vmovapd [rdi + 32], ymm3
        vmovapd [rdi + 64], ymm4
        vmovapd [rdi + 96], ymm5
        ret
