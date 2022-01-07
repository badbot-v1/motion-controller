# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library

cc_library(
    name = "protocode",
    srcs = glob(["cppsrc/*.cc","cppsrc/*.h"]),
    hdrs = glob(["cppsrc/*.h"]),
    strip_include_prefix = "cppsrc",
    deps = [
    ],
    visibility = ["//visibility:public"]
)

cc_library(
    name = "messages",
    srcs = glob(["*.cpp","*.hpp"]),
    hdrs = glob(["*.hpp"]),
    linkstatic = 1,
    deps = [
        ":protocode",
        "//shared/log:mtlogbase",
        "//shared/system:sys",
        "//shared/utils:shared-storage",
        "//shared/gst:gstreamer-io",
        "@yamlcpp//:yaml-cpp",
        "@boost//:signals2",
        "@usr_local//:cppzmq",
        "@usr_local//:protobuf",
    ],
    visibility = ["//visibility:public"]
)