export

HOST := $(shell ./config/util.sh -h)
ARCH := $(shell ./config/util.sh -a $(HOST))

BOOTDIR = /boot
INCLUDEDIR = /include
LIBDIR = /lib
KERNEL = kernel.bin

AR := $(HOST)-ar
AS := $(HOST)-as
CC := $(HOST)-gcc

CFLAGS = -O2 -g -Wall -Wextra
CPPFLAGS =
LDFLAGS =
LIBS =

.PHONY = all koyomin iso clean

all: koyomin

koyomin: clean
	mkdir -p sysroot
	SYSROOT="$(shell pwd)/sysroot" $(MAKE) -C libc install-headers
	SYSROOT="$(shell pwd)/sysroot" $(MAKE) -C kernel install-headers
	SYSROOT="$(shell pwd)/sysroot" $(MAKE) -C libc install
	SYSROOT="$(shell pwd)/sysroot" $(MAKE) -C kernel install

iso: CFLAGS += -g0
iso: koyomin
	mkdir -p isodir/boot/grub
	cp sysroot/boot/$(KERNEL) isodir/boot/
	cp config/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -d /usr/lib/grub/i386-pc/ --fonts= --locales= --themes= -o koyomin.iso isodir

clean:
	$(MAKE) -C libc clean
	$(MAKE) -C kernel clean
	rm -rfv sysroot isodir koyomin.iso
