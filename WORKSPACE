workspace(name = "bsu_cpp")

load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

http_archive(
    name = "catch2",
    sha256 = "122928b814b75717316c71af69bd2b43387643ba076a6ec16e7882bfb2dfacbb",
    strip_prefix = "Catch2-3.4.0",
    urls = ["https://github.com/catchorg/Catch2/archive/refs/tags/v3.4.0.tar.gz"],
)

http_archive(
    name = "hedron_compile_commands",
    sha256 = "ed5aea1dc87856aa2029cb6940a51511557c5cac3dbbcb05a4abd989862c36b4",
    strip_prefix = "bazel-compile-commands-extractor-e16062717d9b098c3c2ac95717d2b3e661c50608",
    url = "https://github.com/hedronvision/bazel-compile-commands-extractor/archive/e16062717d9b098c3c2ac95717d2b3e661c50608.tar.gz",
)

load("@hedron_compile_commands//:workspace_setup.bzl", "hedron_compile_commands_setup")

hedron_compile_commands_setup()

load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

git_repository(
    name = "bazel_clang_tidy",
    commit = "11541864afa832ff6721e479c44794e9c9497ae8",
    remote = "https://github.com/erenon/bazel_clang_tidy.git",
)

# load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_repository")

BAZEL_CLANG_FORMAT_COMMIT = "ad5f2572518053b36a2d999f7b824fb5a7819ab4"

BAZEL_CLANG_FORMAT_SHA = "c31f0ea477dd0da84fc2c694a533797a9d2bf060f8cca8b5ea30402a47a2ea0a"

http_archive(
    name = "bazel_clang_format",
    sha256 = BAZEL_CLANG_FORMAT_SHA,
    strip_prefix = "bazel_clang_format-{commit}".format(
        commit = BAZEL_CLANG_FORMAT_COMMIT,
    ),
    url = "https://github.com/oliverlee/bazel_clang_format/archive/{commit}.tar.gz".format(
        commit = BAZEL_CLANG_FORMAT_COMMIT,
    ),
)