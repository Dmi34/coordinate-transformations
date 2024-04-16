;------------------------------------------------------------------------------
; void RotateI64_avx2(double* x, double* y, double sin, double cos);
;------------------------------------------------------------------------------
        section .text

        global RotateI64_avx2
RotateI64_avx2:
        vbroadcastsd ymm0, r8
        vbroadcastsd ymm1, r9

        vmulpd ymm2, [rcx], ymm1 ; ymm2 = x*cos
        vmulpd ymm3, [rcx], ymm0 ; ymm3 = x*sin
        vmovapd ymm4, [rdx] ; ymm4 = y

        vfnmadd231pd ymm2, ymm4, ymm0 ; ymm2 = -y*sin + x*cos
        vfmadd231pd ymm3, ymm4, ymm1 ; ymm3 = y*cos + x*sin

        vmovapd [rcx], ymm2
        vmovapd [rdx], ymm3
        ret
