load("//tools/bazel:nasm_library.bzl", "nasm_library")
load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

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
    srcs = [":assemble_translate", ":assemble_rotate"],
    hdrs = ["transform.h"],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
        "-O3"
    ]
)

cc_test(
    name = "benchmark_main",
    # size = "small",
    srcs = ["bench.cpp"],
    deps = [
        ":main",
        "@catch2//:catch2_main",
    ],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
        "-O3"
    ]
)

cc_test(
    name = "test_main",
    # size = "small",
    srcs = ["test.cpp"],
    deps = [
        ":main",
        "@catch2//:catch2_main",
    ],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
        "-O3"
    ]
)