#!/bin/bash

source shell-scripts/environment.sh

rm fuse.log
rm vpm.log
rm followfsm.log

tmux new-session -s "$SESSION_NAME" -n "apps" -d
tmux new-window -t "$SESSION_NAME:1" -n "rtspservice"

# Improve colors
#set -g default-terminal 'screen-256color'

# Set scrollback buffer to 10000
#set -g history-limit 10000

# Customize the status line
#set -g status-fg  green
#set -g status-bg  black

# start rtsp server on second window
tmux send-keys 'cd ../gst-rtsp-server && build/rtsp-server mounts.config' C-m;

# split window into two panes vertically
tmux select-window -t "$SESSION_NAME:0"
tmux split-window -v \;

# start fuse in top window
tmux select-pane -t 0 \;
tmux send-keys "bazel-bin/fuse/fuse -c $FUSE_CONFIG_FILE_PATH" C-m;
tmux select-pane -t 1 \;
tmux send-keys "bazel-bin/visual-perceiver/vpm -c $VPM_CONFIG_FILE_PATH" C-m;