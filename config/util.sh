#!/bin/sh

getopts "has" opt

case $opt in
	h) echo "i686-elf" ;;
	a) if [[ $2 == "i686-elf" ]]; then echo "x86"; fi ;;
	s) if [[ $2 == "i686-elf" ]]; then echo "i386"; fi ;;
esac
