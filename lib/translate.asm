;------------------------------------------------------------------------------
; void TranslateF64_asm(PackedPoint* p, Point delta);
;------------------------------------------------------------------------------
        section .text

        global TranslateF64_asm

TranslateI64_avx2:
        int 3
;        vmovapd ymm0, [rcx]
;        vmovapd ymm1, [rdx]
;        vbroadcastsd ymm2, [r8] ; same problem as in rotate broadcastsd
;        vbroadcastsd ymm3, [r9] ; same. Zaglushka
;        vaddpd ymm0, ymm2
;        vaddpd ymm1, ymm3
;        vmovapd [rcx], ymm0
;        vmovapd [rdx], ymm1
        ret