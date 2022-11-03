load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "placeholder",
    srcs = ["placeholder.cc"],
    hdrs = ["placeholder.h"],
)

cc_binary(
    name = "flappyBird",
    srcs = ["flappyBird.cc"],
    deps = [
        ":placeholder",
    ],
)
