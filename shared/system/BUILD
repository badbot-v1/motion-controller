# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "sys",
    srcs = glob(["*.cpp","*.hpp"]),
    hdrs = glob(["*.hpp"]),
    deps = [
        "//shared/log:mtlogbase",
        "@boost//:signals2"
    ],
    visibility = ["//visibility:public"]
)