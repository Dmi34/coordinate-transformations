;------------------------------------------------------------------------------
; void TranslateSinglePointAsm(const PackedPoint* dest, const PackedPoint& p, Point delta);
;------------------------------------------------------------------------------
        section .text

        global TranslateSinglePointAsm
        global TranslateSingleSegmentAsm

TranslateSinglePointAsm:
        vmovaps ymm2, [rsi]
        vmovaps ymm3, [rsi + 32]
        vbroadcastss ymm1, xmm0
        pshufd xmm0, xmm0, 0x55
        vbroadcastss ymm0, xmm0
        vaddps ymm2, ymm1
        vaddps ymm3, ymm0
        vmovaps [rdi], ymm2
        vmovaps [rdi + 32], ymm3
        ret

;-----------------------------------------------------------------------------------------------
; void TranslateSingleSegmentAsm(const PackedSegment* dest, const PackedSegment& s, Point delta);
;-----------------------------------------------------------------------------------------------

TranslateSingleSegmentAsm:
        vmovaps ymm2, [rsi]
        vmovaps ymm3, [rsi + 32]
        vmovaps ymm4, [rsi + 64]
        vmovaps ymm5, [rsi + 96]
        vbroadcastss ymm1, xmm0
        pshufd xmm0, xmm0, 0x55
        vbroadcastss ymm0, xmm0
        vaddps ymm2, ymm1
        vaddps ymm3, ymm0
        vaddps ymm4, ymm1
        vaddps ymm5, ymm0
        vmovaps [rdi], ymm2
        vmovaps [rdi + 32], ymm3
        vmovaps [rdi + 64], ymm4
        vmovaps [rdi + 96], ymm5
        ret