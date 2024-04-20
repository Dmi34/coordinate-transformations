;------------------------------------------------------------------------------
; void RotateF64_asm(PackedPont* p, double sin, double cos);
;------------------------------------------------------------------------------
        section .text

        global RotateF64_asm
RotateF64_asm:
        int 3
;        vbroadcastsd ymm0, [[rdx]] ; zaglushka. Cannot take float from rdx. It is probably stored inside xmm0 by calling convention
;        vbroadcastsd ymm1, [[r8]] ; same
;
;        vmulpd ymm2, ymm1, [rcx] ; ymm2 = x*cos here and in 12 there was invalid order of operands
;        vmulpd ymm3, ymm0, [rcx] ; ymm3 = x*sin
;        vmovapd ymm4, [rcx + 8] ; ymm4 = y
;
;        vfnmadd231pd ymm2, ymm4, ymm0 ; ymm2 = -y*sin + x*cos
;        vfmadd231pd ymm3, ymm4, ymm1 ; ymm3 = y*cos + x*sin
;
;        vmovapd [[rcx]], ymm2
;        vmovapd [[rcx + 8]], ymm3
        ret