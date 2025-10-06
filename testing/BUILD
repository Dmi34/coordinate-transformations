load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

genrule(
   name = "assemble_translate_pd",
   srcs = ["translate_pd.asm"],
   outs = ["assemble_translate_pd.o"],
   cmd = "nasm -f elf64 -o $@ $(location translate_pd.asm)",
)

genrule(
   name = "assemble_rotate_pd",
   srcs = ["rotate_pd.asm"],
   outs = ["assemble_rotate_pd.o"],
   cmd = "nasm -f elf64 -o $@ $(location rotate_pd.asm)",
)

cc_library(
    name = "main_pd",
    srcs = [":assemble_translate_pd", ":assemble_rotate_pd"],
    hdrs = ["transform.h"],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
#        "-O3"
    ]
)

cc_test(
    name = "benchmark_pd",
    srcs = ["bench_pd.cpp"],
    deps = [
        ":main_pd",
        "@catch2//:catch2_main",
    ],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
#        "-O3"
    ]
)

cc_test(
    name = "test_pd",
    srcs = ["test_pd.cpp"],
    deps = [
        ":main_pd",
        "@catch2//:catch2_main",
    ],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
#        "-O3"
    ]
)


genrule(
    name = "assemble_translate_ps",
    srcs = ["translate_ps.asm"],
    outs = ["assemble_translate_ps.o"],
    cmd = "nasm -f elf64 -o $@ $(location translate_ps.asm)",
)

genrule(
    name = "assemble_rotate_ps",
    srcs = ["rotate_ps.asm"],
    outs = ["assemble_rotate_ps.o"],
    cmd = "nasm -f elf64 -o $@ $(location rotate_ps.asm)",
)

cc_library(
    name = "main_ps",
    srcs = [":assemble_translate_ps", ":assemble_rotate_ps"],
    hdrs = ["transform.h"],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
#        "-O3"
    ]
)

cc_test(
    name = "benchmark_ps",
    srcs = ["bench_ps.cpp"],
    deps = [
        ":main_ps",
        "@catch2//:catch2_main",
    ],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
#        "-O3"
    ]
)

cc_test(
    name = "test_ps",
    srcs = ["test_ps.cpp"],
    deps = [
        ":main_ps",
        "@catch2//:catch2_main",
    ],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
#        "-O3"
    ]
)