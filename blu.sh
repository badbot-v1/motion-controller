#!/bin/sh
echo "Building on laptop - utilities"

bazel build //lidarexplorer:lidarexplorer --define plat=laptop
bazel build //lidarexplorer:l2i --define plat=laptop