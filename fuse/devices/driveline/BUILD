cc_library(
    name = "driveline",
    srcs = glob(["*.cpp","*.hpp"]),
    deps = [
        "//shared/utils:shared-storage",
        "//shared/log:mtlogbase",
        "//shared/drawing:drawing",
        "//shared/system:sys",
        "//fuse/devices:sensors",
        "@yamlcpp//:yaml-cpp",
        "@thirdparty//:spdlog",
        "@boost//:signals2"
    ],
    copts = ["-fopenmp"],
    linkopts = ["-pthread","-lgomp"],
    visibility = ["//visibility:public"]
)