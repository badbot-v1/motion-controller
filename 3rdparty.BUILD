
cc_library(
    name = "cxxopts",
    hdrs = ["cxxopts-2.2.0/include/cxxopts.hpp"],
    strip_include_prefix = "cxxopts-2.2.0/include",
    include_prefix = "cxxopts",
    visibility = ["//visibility:public"],
  #static_library = "libmylib.a",
  # If alwayslink is turned on,
  # libmylib.a will be forcely linked into any binary that depends on it.
  # alwayslink = 1,
)

cc_library(
    name = "ydlidar",
    srcs = ["ydlidar/build/libydlidar_driver.a"],
    hdrs = glob(["ydlidar/include/**/*"]),
    strip_include_prefix = "ydlidar/include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "darknet",
    srcs = ["darknet/libdarknet.so"],
    hdrs = glob(["darknet/include/*.h","darknet/include/*.hpp"]),
    strip_include_prefix = "darknet/include",
    include_prefix = "dnet",
    visibility = ["//visibility:public"],
)


cc_library(
    name = "spdlog",
    srcs = ["spdlog/build/libspdlog.a"],
    hdrs = glob(["spdlog/include/**/*"]),
    strip_include_prefix = "spdlog/include",
    visibility = ["//visibility:public"],
)


cc_library(
    name = "zmqwsock",
    srcs = glob(["zwssock/src/CZMQ-ZWSSock/*.c"]),
    hdrs = glob(["zwssock/src/CZMQ-ZWSSock/*.h"]),
    strip_include_prefix = "zwssock/src/CZMQ-ZWSSock",
    visibility = ["//visibility:public"],
)
