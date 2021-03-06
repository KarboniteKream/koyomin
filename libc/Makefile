CFLAGS ?= -O2 -g

CFLAGS := $(CFLAGS)
CPPFLAGS := $(CPPFLAGS) -Iinclude
LDFLAGS := $(LDFLAGS)

LIBK_CFLAGS := $(CFLAGS) -ffreestanding -fbuiltin
LIBK_CPPFLAGS := $(CPPFLAGS) -D__is_kernel
LIBK_LDFLAGS := $(LIBK_LDFLAGS)

ARCHDIR := arch/$(ARCH)
include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(ARCH_CFLAGS)
CPPFLAGS := $(CPPFLAGS) $(ARCH_CPPFLAGS)
LIBK_CFLAGS := $(LIBK_CFLAGS) $(KERNEL_ARCH_CFLAGS)
LIBK_CPPFLAGS := $(LIBK_CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)

FREEOBJS := $(ARCH_FREEOBJS) \
	stdio/printf.o \
	stdio/putchar.o \
	stdio/puts.o \
	stdlib/abort.o \
	stdlib/exit.o \
	string/memcmp.o \
	string/memcpy.o \
	string/memmove.o \
	string/memset.o \
	string/strlen.o

HOSTEDOBJS := $(ARCH_HOSTEDOBJS)

OBJS := $(FREEOBJS) $(HOSTEDOBJS)
LIBK_OBJS := $(FREEOBJS:.o=.libk.o)

BINARIES = libc.a libk.a $(ARCHDIR)/crt0.o $(ARCHDIR)/crti.o $(ARCHDIR)/crtn.o

.PHONY: all clean install install-headers install-libs

all: $(BINARIES)

libc.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libk.a: $(LIBK_OBJS)
	$(AR) rcs $@ $(LIBK_OBJS)

%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

%.o: %.S
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

%.libk.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

%.libk.o: %.S
	$(CC) -c $< -o $@ $(LIBK_CFLAGS) $(LIBK_CPPFLAGS)

clean:
	rm -f $(BINARIES) $(OBJS) $(LIBK_OBJS)
	find . -type f -name "*.o" -delete

install: install-headers install-libs

install-headers:
	mkdir -p $(SYSROOT)$(INCLUDEDIR)
	cp -RTv include $(SYSROOT)$(INCLUDEDIR)

install-libs: $(BINARIES)
	mkdir -p $(SYSROOT)$(LIBDIR)
	cp $(BINARIES) $(SYSROOT)$(LIBDIR)
