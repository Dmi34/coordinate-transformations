;------------------------------------------------------------------------------
; void RotateP64_asm(PackedPont* p, double sin, double cos);
;------------------------------------------------------------------------------
        section .text

        global RotateP64_asm
RotateP64_asm:
        vbroadcastsd ymm0, xmm0
        vbroadcastsd ymm1, xmm1
        mov rax, [rdi]
        vmulpd ymm2, ymm1, [rax] ; ymm2 = x*cos
        vmulpd ymm3, ymm0, [rax] ; ymm3 = x*sin
        mov rax, [rdi + 8]
        vmovapd ymm4, [rax] ; ymm4 = y
        vfnmadd231pd ymm2, ymm4, ymm0 ; ymm2 = -y*sin + x*cos
        vfmadd231pd ymm3, ymm4, ymm1 ; ymm3 = y*cos + x*sin
        mov rax, [rdi]
        vmovapd [rax], ymm2
        mov rax, [rdi + 8]
        vmovapd [rax], ymm3
        ret