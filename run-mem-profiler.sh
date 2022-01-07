#!/bin/sh
valgrind --tool=massif bazel-bin/fuse/fuse -c ./config/config.yml