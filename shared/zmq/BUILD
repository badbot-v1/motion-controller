# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "websockets",
    srcs = glob(["*.cpp","*.hpp"]),
    hdrs = glob(["*.hpp"]),
    deps = [
        "@thirdparty//:zmqwsock",
        "//shared/messaging:messages",
        "//shared/log:mtlogbase",
        "//shared/system:sys",
        "@boost//:signals2"
    ],
    visibility = ["//visibility:public"]
)