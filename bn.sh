#!/bin/sh
echo "Building on nano"

bazel build --cxxopt='-std=c++14' //fuse:fuse --define plat=nano $1
bazel build --cxxopt='-std=c++14' //visual-perceiver:vpm --define plat=nano $1
#bazel build --cxxopt='-std=c++14' //camfeed:camfeed --define plat=nano $1