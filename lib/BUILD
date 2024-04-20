load("//tools/bazel:nasm_library.bzl", "nasm_library")
load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

# nasm_library(
#     name = "avx2",
#     srcs = [
#         "translate.asm", "rotate.asm"
#     ],
#     hdrs = [
#         "ModX86Asm3eNASM.inc"
#     ],
#     copts = [
#         "-m64",
#         "-mavx2",
#     ]
# )

genrule(
    name = "assemble_translate",
    srcs = ["translate.asm"],
    outs = ["assemble_translate.o"],
    cmd = "nasm -f elf64 -g -F dwarf -o $@ $(location translate.asm)",
)

genrule(
    name = "assemble_rotate",
    srcs = ["rotate.asm"],
    outs = ["assemble_rotate.o"],
    cmd = "nasm -f elf64 -g -F dwarf -o $@ $(location rotate.asm)",
)

cc_library(
    name = "main",
    srcs = ["translate.cpp", "rotate.cpp", ":assemble_translate", ":assemble_rotate"],
    hdrs = ["transform.h"],
    copts = [
        "-m64",
        "-mavx2",
        # "-mavx512f",
        # "-mavx512er",
        "-O3"
    ]
)

cc_test(
    name = "benchmark_main",
    # size = "small",
    srcs = ["bench.cpp"],
    deps = [
        ":main",
        "//tools/bazel:catch2",
    ]
)

cc_test(
    name = "test_main",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":main",
        "//tools/bazel:catch2",
    ]
)