#!/bin/sh
sudo mkdir -p ~/mnt/nanofs
sudo sshfs -o allow_other faisal@10.42.0.1:/ ~/mnt/nanofs
