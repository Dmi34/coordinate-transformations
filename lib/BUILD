load("//tools/bazel:nasm_library.bzl", "nasm_library")
load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

genrule(
    name = "assemble_translate64",
    srcs = ["translate64.asm"],
    outs = ["assemble_translate64.o"],
    cmd = "nasm -f elf64 -g -F dwarf -o $@ $(location translate64.asm)",
)

genrule(
    name = "assemble_rotate64",
    srcs = ["rotate64.asm"],
    outs = ["assemble_rotate64.o"],
    cmd = "nasm -f elf64 -g -F dwarf -o $@ $(location rotate64.asm)",
)

cc_library(
    name = "main64",
    srcs = [":assemble_translate64", ":assemble_rotate64"],
    hdrs = ["transform64.h"],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
        "-O3"
    ]
)

cc_test(
    name = "benchmark64",
    # size = "small",
    srcs = ["bench64.cpp"],
    deps = [
        ":main64",
        "@catch2//:catch2_main",
    ],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
        "-O3"
        # "-O2",
        # "-fgcse-after-reload",
        # "-fipa-cp-clone",
        # "-floop-interchange",
        # "-floop-unroll-and-jam",
        # "-fpeel-loops",
        # "-fpredictive-commoning",
        # "-fsplit-loops",
        # "-fsplit-paths",
        # "-ftree-loop-distribution",
        # "-ftree-partial-pre",
        # "-funswitch-loops",
        # "-fvect-cost-model=dynamic",
        # "-fversion-loops-for-strides",
    ]
)

cc_test(
    name = "test64",
    # size = "small",
    srcs = ["test64.cpp"],
    deps = [
        ":main64",
        "@catch2//:catch2_main",
    ],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
        "-O3"
    ]
)


genrule(
    name = "assemble_translate32",
    srcs = ["translate32.asm"],
    outs = ["assemble_translate32.o"],
    cmd = "nasm -f elf64 -g -F dwarf -o $@ $(location translate32.asm)",
)

genrule(
    name = "assemble_rotate32",
    srcs = ["rotate32.asm"],
    outs = ["assemble_rotate32.o"],
    cmd = "nasm -f elf64 -g -F dwarf -o $@ $(location rotate32.asm)",
)

cc_library(
    name = "main32",
    srcs = [":assemble_translate32", ":assemble_rotate32"],
    hdrs = ["transform32.h"],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
        "-O3"
    ]
)

cc_test(
    name = "benchmark32",
    # size = "small",
    srcs = ["bench32.cpp"],
    deps = [
        ":main32",
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
    name = "test32",
    # size = "small",
    srcs = ["test32.cpp"],
    deps = [
        ":main32",
        "@catch2//:catch2_main",
    ],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
        "-O3"
    ]
)