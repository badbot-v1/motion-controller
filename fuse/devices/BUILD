cc_library(
    name = "sensors",
    srcs = glob(["*.cpp","*.hpp"]),
    deps = [
        "//shared/utils:shared-storage",
        "//shared/log:mtlogbase",
        "//shared/system:sys",
        "//shared/messaging:protocode",
        "//shared/messaging:messages",
        "@yamlcpp//:yaml-cpp",
        "@thirdparty//:spdlog",
        "@boost//:signals2"
    ],
    copts = ["-fopenmp"],
    linkopts = ["-pthread","-lgomp","-lgps"],
    visibility = ["//visibility:public"]
)