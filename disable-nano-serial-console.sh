#!/bin/sh

sudo systemctl stop nvgetty
sudo systemctl disable nvgetty
sudo udevadm trigger