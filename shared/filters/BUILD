# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "kalman",
    srcs = glob(["*.cpp","*.hpp"]),
    hdrs = glob(["*.hpp"]),
    deps = [
        "@boost//:signals2",
        "//shared/system:sys",
        "//shared/log:mtlogbase",
    ],
    visibility = ["//visibility:public"]
)