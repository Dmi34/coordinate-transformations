;------------------------------------------------------------------------------
; void TranslateP64_asm(PackedPoint* p, Point delta);
;------------------------------------------------------------------------------
        section .text

        global TranslateP64_asm

TranslateP64_asm:
        mov rax, [rdi]
        vmovapd ymm2, [rax]
        mov rax, [rdi + 8]
        vmovapd ymm3, [rax]
        vbroadcastsd ymm0, xmm0
        vbroadcastsd ymm1, xmm1
        vaddpd ymm2, ymm0
        vaddpd ymm3, ymm1
        mov rax, [rdi]
        vmovapd [rax], ymm2
        mov rax, [rdi + 8]
        vmovapd [rax], ymm3
        ret