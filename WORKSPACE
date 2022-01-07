load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")
load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")

git_repository(
    name = "com_github_nelhage_rules_boost",
    commit = "6d6fd834281cb8f8e758dd9ad76df86304bf1869",
    remote = "https://github.com/faisalthaheem/rules_boost",
)

load("@com_github_nelhage_rules_boost//:boost/boost.bzl", "boost_deps")
boost_deps()

new_local_repository(
    name="gstreamer",
    path="/usr",
    build_file="gstreamer.BUILD"
)

new_local_repository(
    name = "opencv",
    path = "/usr",
    build_file = "opencv.BUILD",
)

local_repository(
    name = "yamlcpp",
    path = "../deps/yaml-cpp"
)

new_local_repository(
    name = "thirdparty",
    path = "../deps/",
    build_file = "3rdparty.BUILD",
)

new_local_repository(
    name = "qt",
    path = "/usr/include/x86_64-linux-gnu/qt5",
    build_file = "BUILD.qt"
)

new_local_repository(
    name = "usr_local",
    path = "/usr/local",
    build_file = "usr_local.BUILD"
)

git_repository(
    name = "gtest",
    remote = "https://github.com/google/googletest",
    branch = "v1.10.x",
)