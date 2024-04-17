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

cc_library(
    name = "main",
    srcs = ["translate.cpp", "rotate.cpp"],
    hdrs = ["transform.h"],
    copts = [
        "-m64",
        "-mavx512f",
        "-mavx512er",
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