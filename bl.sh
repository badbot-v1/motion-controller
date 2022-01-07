#!/bin/sh
echo "Building on laptop"

bazel build --cxxopt='-std=c++14' //fuse:fuse --define plat=laptop $1
bazel build --cxxopt='-std=c++14' //visual-perceiver:vpm --define plat=laptop $1
#bazel build --cxxopt='-std=c++14' //camfeed:camfeed --define plat=laptop $1
