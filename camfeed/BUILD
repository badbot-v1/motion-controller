cc_binary(
    name = "camfeed",
    srcs = glob(["*.cpp","*.hpp"]),
    deps = [
        "//shared/gst:gstreamer-io",
        "//shared/utils:shared-storage",
        "//shared/log:mtlogbase",
        "//shared/messaging:protocode",
        "//shared/messaging:messages",
        "//shared/system:sys",
        "@yamlcpp//:yaml-cpp",
        "@thirdparty//:cxxopts",
        "@thirdparty//:spdlog",
    ],
    copts = ["-fopenmp"],
    linkopts = ["-pthread","-lz","-lgomp"],
)