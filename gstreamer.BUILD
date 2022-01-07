config_setting(
    name = "x86_64_build",
    values = {"define":"plat=laptop"}
)

config_setting(
    name = "arm_build",
    #values = {"cpu":"aarch64"}
    values = {"define":"plat=nano"}
)

cc_library(
    name="sigc++-config",
    hdrs = select({
        ":x86_64_build" : glob(["lib/x86_64-linux-gnu/sigc++-2.0/include/*.h"]),
        ":arm_build" : glob(["lib/aarch64-linux-gnu/sigc++-2.0/include/*.h"]),
    }),
    copts = select({
        ":x86_64_build" : ["-Ilib/x86_64-linux-gnu/sigc++-2.0/include"],
        ":arm_build" : ["-Ilib/aarch64-linux-gnu/sigc++-2.0/include"],
    }),
    strip_include_prefix = select({
        ":x86_64_build" : "lib/x86_64-linux-gnu/sigc++-2.0/include",
        ":arm_build" : "lib/aarch64-linux-gnu/sigc++-2.0/include",
    }),
    visibility = ["//visibility:public"], 
    linkstatic = 0,
    deps = [
    ]
)

cc_library(
    name="sigc++",
    hdrs = glob(["include/sigc++-2.0/**/*"]),
    srcs= select({
        ":x86_64_build" : ["lib/x86_64-linux-gnu/libsigc-2.0.so"],
        ":arm_build" : ["lib/aarch64-linux-gnu/libsigc-2.0.so"],
    }),
    copts = ["-Iinclude/sigc++-2.0"],
    strip_include_prefix = "include/sigc++-2.0",
    visibility = ["//visibility:public"], 
    linkstatic = 0,
    deps = [
        ":sigc++-config"
    ]
)

cc_library(
    name="giomm-config",
    srcs = select({
        ":x86_64_build" : glob(["lib/x86_64-linux-gnu/giomm-2.4/libgiomm-2.4.so"]),
        ":arm_build" : glob(["lib/aarch64-linux-gnu/giomm-2.4/libgiomm-2.4.so"]),
    }),
    hdrs = select({
        ":x86_64_build" : glob(["lib/x86_64-linux-gnu/giomm-2.4/include/*.h"]),
        ":arm_build" : glob(["lib/aarch64-linux-gnu/giomm-2.4/include/*.h"]),
    }),
    copts = select({
        ":x86_64_build" : ["-Ilib/x86_64-linux-gnu/giomm-2.4/include"],
        ":arm_build" : ["-Ilib/aarch64-linux-gnu/giomm-2.4/include"],
    }),
    strip_include_prefix = select({
        ":x86_64_build" : "lib/x86_64-linux-gnu/giomm-2.4/include",
        ":arm_build" : "lib/aarch64-linux-gnu/giomm-2.4/include",
    }),
    visibility = ["//visibility:public"], 
    linkstatic = 0,
    deps = [
    ]
)

cc_library(
    name="giomm",
    hdrs = glob(["include/giomm-2.4/**/*"]),
    copts = ["-Iinclude/giomm-2.4"],
    strip_include_prefix = "include/giomm-2.4",
    visibility = ["//visibility:public"], 
    linkstatic = 0,
    deps = [
        ":giomm-config"
    ]
)

cc_library(
    name = "glibconfig",
    hdrs = select({
        ":x86_64_build" : glob(["lib/x86_64-linux-gnu/glib-2.0/include/**/*"]),
        ":arm_build" : glob(["lib/aarch64-linux-gnu/glib-2.0/include/**/*"]),
    }),
    copts = select({
        ":x86_64_build" : ["-Ilib/x86_64-linux-gnu/glib-2.0/include/"],
        ":arm_build" : ["-Ilib/aarch64-linux-gnu/glib-2.0/include/"],
    }),
    strip_include_prefix = select({
        ":x86_64_build" : "lib/x86_64-linux-gnu/glib-2.0/include",
        ":arm_build" : "lib/aarch64-linux-gnu/glib-2.0/include",
    }),
    visibility = ["//visibility:public"],
    linkstatic = 0,
)

cc_library(
    name = "glibmmconfig",
    hdrs = select({
        ":x86_64_build" : glob(["lib/x86_64-linux-gnu/glibmm-2.4/include/*.h"]),
        ":arm_build" : glob(["lib/aarch64-linux-gnu/glibmm-2.4/include/*.h"]),
    }),
    copts = select({
        ":x86_64_build" : ["-Ilib/x86_64-linux-gnu/glibmm-2.4/include"],
        ":arm_build" : ["-Ilib/aarch64-linux-gnu/glibmm-2.4/include"],
    }),
    strip_include_prefix = select({
        ":x86_64_build" : "lib/x86_64-linux-gnu/glibmm-2.4/include/",
        ":arm_build" : "lib/aarch64-linux-gnu/glibmm-2.4/include/",
    }),
    visibility = ["//visibility:public"],
    linkstatic = 0,
)


cc_library(
    name = "glib",
    srcs = select({
        ":x86_64_build" : ["lib/x86_64-linux-gnu/libglib-2.0.so"],
        ":arm_build" : ["lib/aarch64-linux-gnu/libglib-2.0.so"],
    }),
    hdrs = glob(["include/glib-2.0/**/*"]),
    copts = ["-Iinclude/glib-2.0"],
    strip_include_prefix = "include/glib-2.0",
    visibility = ["//visibility:public"], 
    linkstatic = 0,
    deps = [
        ":glibconfig"
    ]
)

cc_library(
    name = "glibmm",
    srcs = select({
        ":x86_64_build" : ["lib/x86_64-linux-gnu/libglibmm-2.4.so","lib/x86_64-linux-gnu/libglibmm_generate_extra_defs-2.4.so"],
        ":arm_build" : ["lib/aarch64-linux-gnu/libglibmm-2.4.so","lib/aarch64-linux-gnu/libglibmm_generate_extra_defs-2.4.so"],
    }),
    hdrs = glob(["include/glibmm-2.4/**/*"]),
    copts = ["-Iinclude/glibmm-2.4"],
    strip_include_prefix = "include/glibmm-2.4",
    visibility = ["//visibility:public"], 
    linkstatic = 0,
    deps = [
        ":glibmmconfig",
        ":sigc++"
    ]
)



cc_library(
    name = "core",
    srcs = select({
        ":x86_64_build" :glob(["lib/x86_64_build/gstreamer-1.0/*.so"]),
        ":arm_build" :glob(["lib/aarch64-linux-gnu/gstreamer-1.0/*.so"]),
    }),
    hdrs = glob(["include/gstreamer-1.0/gst/**/*"]),
    copts = ["-Iinclude/gstreamer-1.0"],
    strip_include_prefix = "include/gstreamer-1.0",
    visibility = ["//visibility:public"], 
    linkstatic = 0,
    deps = [
        ":glib"
    ]
)

cc_library(
    name = "gstreamermm-config",
    hdrs = select({
        ":x86_64_build" :glob(["lib/x86_64-linux-gnu/gstreamermm-1.0/include/*.h"]),
        ":arm_build" :glob(["lib/aarch64-linux-gnu/gstreamermm-1.0/include/*.h"]),
    }),
    strip_include_prefix = select({
        ":x86_64_build" : "lib/x86_64-linux-gnu/gstreamermm-1.0/include",
        ":arm_build" : "lib/aarch64-linux-gnu/gstreamermm-1.0/include",
    }),
    copts = select({
        ":x86_64_build" : ["-Ilib/x86_64-linux-gnu/gstreamermm-1.0/include"],
        ":arm_build" : ["-Ilib/aarch64-linux-gnu/gstreamermm-1.0/include"],
    }),
    visibility = ["//visibility:public"], 
    linkstatic = 0,
    deps = [
    ]
)

cc_library(
    name = "gstreamermm",
    srcs = select({
        ":x86_64_build" : ["lib/x86_64-linux-gnu/libgstreamermm-1.0.so"],
        ":arm_build" : ["lib/aarch64-linux-gnu/libgstreamermm-1.0.so"],
    }),
    hdrs = glob(["include/gstreamermm-1.0/**/*"]),
    strip_include_prefix = "include/gstreamermm-1.0",
    copts = ["-Iinclude/gstreamermm-1.0"],
    visibility = ["//visibility:public"], 
    linkstatic = 0,
    deps = [
        "gstreamermm-config",
        ":glib",
        ":glibmm",
        ":giomm"
    ]
)
