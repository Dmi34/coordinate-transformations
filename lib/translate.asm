;------------------------------------------------------------------------------
; void Translate_asm(PackedPoint* target, const PackedPoint& p, Point delta);
;------------------------------------------------------------------------------
        section .text

        global Translate_asm

Translate_asm:
        vmovapd ymm2, [rsi]
        vmovapd ymm3, [rsi + 32]
        vbroadcastsd ymm0, xmm0
        vbroadcastsd ymm1, xmm1
        vaddpd ymm2, ymm0
        vaddpd ymm3, ymm1
        vmovapd [rdi], ymm2
        vmovapd [rdi + 32], ymm3
        ret