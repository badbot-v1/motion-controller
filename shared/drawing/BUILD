cc_library(
    name = "drawing",
    srcs = glob(["*.hpp","*.cpp"]),
    hdrs = glob(["*.hpp"]),
    deps = [
        "//shared/log:mtlogbase",
        "@opencv//:all",
        "@thirdparty//:ydlidar",
    ],
    copts = ["-fopenmp"],
    linkopts = ["-lgomp"],
    visibility = ["//visibility:public"]
)