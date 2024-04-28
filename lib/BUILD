load("@rules_cc//cc:defs.bzl", "cc_library", "cc_test")

cc_library(
    name = "main",
    hdrs = ["transform.h"],
    copts = [
        "-m64",
        "-mavx2",
        "-mfma",
        "-O3"
    ]
)

cc_test(
    name = "benchmark",
    srcs = ["benchmark.cpp"],
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
