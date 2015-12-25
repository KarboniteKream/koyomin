export

PROJECTS = "libc kernel"

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
CC := $(HOST)-gcc --sysroot=$(shell pwd)/sysroot -isystem=$(INCLUDEDIR)

.PHONY = all clean iso koyomin release

all: koyomin

koyomin:
	mkdir -p sysroot
	@PROJECTS=$(PROJECTS); \
	for PROJECT in $$PROJECTS; do \
		DESTDIR="$(shell pwd)/sysroot" $(MAKE) -C $$PROJECT install-headers; \
	done; \
	for PROJECT in $$PROJECTS; do \
		DESTDIR="$(shell pwd)/sysroot" $(MAKE) -C $$PROJECT install; \
	done

clean:
	@PROJECTS=$(PROJECTS); \
	for PROJECT in $$PROJECTS; do \
		$(MAKE) -C $$PROJECT clean; \
	done
	rm -rfv sysroot isodir koyomin.iso

iso: koyomin
	mkdir -p isodir/boot/grub
	cp sysroot/boot/kernel isodir/boot/kernel
	cp config/grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -d /usr/lib/grub/i386-pc/ --fonts= --locales= --themes= -o koyomin.iso isodir

release: CFLAGS += -g0
release: iso
