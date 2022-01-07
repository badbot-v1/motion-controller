# https://docs.bazel.build/versions/master/be/c-cpp.html#cc_library
cc_library(
    name = "mtlogbase",
    srcs = glob(["*.cpp","*.hpp"]),
    hdrs = glob(["*.hpp"]),
    include_prefix = "mtlog",
    deps = [
        "//shared/utils:shared-storage",
        "@yamlcpp//:yaml-cpp",
        "@thirdparty//:spdlog",
    ],
    visibility = ["//visibility:public"]
)