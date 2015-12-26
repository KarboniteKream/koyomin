export

HOST := $(shell ./config/util.sh -h)

PREFIX = /usr
BOOTDIR = /boot
LIBDIR := $(PREFIX)/lib
INCLUDEDIR := $(PREFIX)/include

CFLAGS = -O2 -g
CPPFLAGS =
LDFLAGS =
LIBS =

AR := $(HOST)-ar
AS := $(HOST)-as
CC := $(HOST)-gcc --sysroot=$(shell pwd)/sysroot

.PHONY = all clean iso koyomin

all: koyomin

koyomin:
	mkdir -p sysroot
	DESTDIR="$(shell pwd)/sysroot" $(MAKE) -C libc install-headers
	DESTDIR="$(shell pwd)/sysroot" $(MAKE) -C kernel install-headers
	DESTDIR="$(shell pwd)/sysroot" $(MAKE) -C libc install
	DESTDIR="$(shell pwd)/sysroot" $(MAKE) -C kernel install

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C kernel clean
	rm -rfv sysroot isodir koyomin.iso

iso: CFLAGS += -g0
iso: koyomin
	mkdir -p isodir/boot/grub
	cp sysroot/boot/kernel isodir/boot/kernel
	cp config/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -d /usr/lib/grub/i386-pc/ --fonts= --locales= --themes= -o koyomin.iso isodir
