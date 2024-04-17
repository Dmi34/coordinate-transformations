;------------------------------------------------------------------------------
; void TranslateI64_avx2(double* x, double* y, double dx, double dy);
;------------------------------------------------------------------------------
        section .text

        global TranslateI64_avx2

TranslateI64_avx2:
        vmovapd ymm0, [rcx]
        vmovapd ymm1, [rdx]
        vbroadcastsd ymm2, r8
        vbroadcastsd ymm3, r9
        vaddpd ymm0, ymm2
        vaddpd ymm1, ymm3
        vmovapd [rcx], ymm0
        vmovapd [rdx], ymm1
        ret