#!/bin/sh

getopts "has" opt

case $opt in
	h) echo "i686-koyomin" ;;
	a) if [[ $2 == "i686-koyomin" ]]; then echo "x86"; fi ;;
	s) if [[ $2 == "i686-koyomin" ]]; then echo "i386"; fi ;;
esac
