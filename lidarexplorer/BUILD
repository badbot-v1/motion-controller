load("//tools/build_rules:qt.bzl", "qt_cc_library")

cc_binary(
    name = "lidarexplorer",
    srcs = ["main.cpp"],
    copts = [
        '-fpic',
    ],
    deps = [
        ":mainwindow",
        "@qt//:qt_widgets",
    ],
)

qt_cc_library(
    name = "mainwindow",
    src = "mainwindow.cpp",
    hdr = "mainwindow.h",
    copts = [
        '-fpic',
    ],
    deps = [
        "@qt//:qt_core",
        "@qt//:qt_widgets",
        "@qt//:qt_gui",
        "@opencv//:all",
        "@thirdparty//:ydlidar",
        "@yamlcpp//:yaml-cpp",
        "//shared/drawing:drawing",
    ],
    ui = "mainwindow.ui",
    ui_deps = [
        "@qt//:qt_widgets",
    ],
)

cc_binary(
    name="l2i",
    srcs = ["main-l2i.cpp"],
    copts = [
    ],
    linkopts = [
        "-lstdc++fs"
    ],
    deps = [
        "@opencv//:all",
        "@thirdparty//:ydlidar",
        "//shared/drawing:drawing",
    ],
)