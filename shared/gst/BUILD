cc_library(
    name = "gstreamer-io",
    srcs = glob(["*.cpp","*.hpp"]),
    deps = [
        "//shared/utils:shared-storage",
        "//shared/log:mtlogbase",
        "//shared/system:sys",
        "@yamlcpp//:yaml-cpp",
        "@opencv//:all",
        "@thirdparty//:spdlog",
        "@boost//:signals2",
        "@gstreamer//:glib",
        "@gstreamer//:core",
        "@gstreamer//:gstreamermm",
    ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"]
)