;------------------------------------------------------------------------------
; void RotateF64_asm(PackedPoint* p, double sin, double cos);
;------------------------------------------------------------------------------
        section .text

        global RotateI64_avx2
RotateI64_avx2:
        vbroadcastsd ymm0, rdx
        vbroadcastsd ymm1, r8

        vmulpd ymm2, [[rcx]], ymm1 ; ymm2 = x*cos
        vmulpd ymm3, [[rcx]], ymm0 ; ymm3 = x*sin
        vmovapd ymm4, [[rcx + 8]] ; ymm4 = y

        vfnmadd231pd ymm2, ymm4, ymm0 ; ymm2 = -y*sin + x*cos
        vfmadd231pd ymm3, ymm4, ymm1 ; ymm3 = y*cos + x*sin

        vmovapd [[rcx]], ymm2
        vmovapd [[rcx + 8]], ymm3
        ret
