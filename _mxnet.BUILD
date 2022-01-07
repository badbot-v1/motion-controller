cc_library(
    name = "core",
    srcs = ["build/libmxnet.so"],
    hdrs = glob(["include/**/*"]),
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cpp-package",
    hdrs = glob(["cpp-package/include/mxnet-cpp/*.h","cpp-package/include/mxnet-cpp/*.hpp"]),
    strip_include_prefix = "cpp-package/include",
    visibility = ["//visibility:public"],
)