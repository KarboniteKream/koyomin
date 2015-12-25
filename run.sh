#!/bin/sh
HOST=$(./config/util.sh -h)
qemu-system-$(./config/util.sh -s $HOST) -cdrom koyomin.iso
