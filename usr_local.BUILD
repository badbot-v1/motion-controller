cc_library(
    name = "zmq",
    srcs = ["lib/libzmq.so"],
    hdrs = ["include/zmq.h","include/zmq_utils.h"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "cppzmq",
    srcs = ["include/zmq.hpp"],
    hdrs = ["include/zmq.hpp"],
    deps = [":zmq"],
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)

cc_library(
    name = "protobuf",
    srcs = ["lib/libprotobuf.so"],
    hdrs = glob(["include/google/**/*.h","include/google/*.h"]),
    strip_include_prefix = "include",
    visibility = ["//visibility:public"],
)