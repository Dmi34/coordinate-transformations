        section .text

        global TranslateDoublePointAsm
        global TranslateDoubleSegmentAsm

;------------------------------------------------------------------------------
; void TranslateDoublePointAsm(const PackedPoint* dest, const PackedPoint& p, Point delta);
;------------------------------------------------------------------------------
TranslateDoublePointAsm:
        vbroadcastsd ymm0, xmm0
        vbroadcastsd ymm1, xmm1
        vaddpd ymm0, [rsi]
        vaddpd ymm1, [rsi + 32]
        vmovapd [rdi], ymm0
        vmovapd [rdi + 32], ymm1
        ret

;-----------------------------------------------------------------------------------------------
; void TranslateDoubleSegmentAsm(const PackedSegment* dest, const PackedSegment& s, Point delta);
;-----------------------------------------------------------------------------------------------
TranslateDoubleSegmentAsm:
        vmovapd ymm2, [rsi]
        vmovapd ymm3, [rsi + 32]
        vmovapd ymm4, [rsi + 64]
        vmovapd ymm5, [rsi + 96]
        vbroadcastsd ymm0, xmm0
        vbroadcastsd ymm1, xmm1
        vaddpd ymm2, ymm0
        vaddpd ymm3, ymm1
        vaddpd ymm4, ymm0
        vaddpd ymm5, ymm1
        vmovapd [rdi], ymm2
        vmovapd [rdi + 32], ymm3
        vmovapd [rdi + 64], ymm4
        vmovapd [rdi + 96], ymm5
        ret