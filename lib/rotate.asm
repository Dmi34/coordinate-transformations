;------------------------------------------------------------------------------
; void Rotate_asm(const PackedPoint* target, const PackedPoint& p, DoubleDirection dir);
;------------------------------------------------------------------------------
        section .text

        global Rotate_asm
Rotate_asm:
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