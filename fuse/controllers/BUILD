cc_library(
    name = "controllers",
    srcs = glob(["*.cpp","*.hpp"]),
    deps = [
        "//shared/utils:shared-storage",
        "//shared/log:mtlogbase",
        "//shared/fsm:fsm",
        "//shared/system:sys",
        "@yamlcpp//:yaml-cpp",
        "@thirdparty//:spdlog",
        "@boost//:signals2"
    ],
    linkopts = ["-pthread"],
    visibility = ["//visibility:public"]
)