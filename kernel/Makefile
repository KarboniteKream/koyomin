CFLAGS := $(CFLAGS) -ffreestanding -fbuiltin
CPPFLAGS := $(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS := $(LDFLAGS)
LIBS := $(LIBS) -nostdlib -lk -lgcc

ARCHDIR := arch/$(ARCH)
include $(ARCHDIR)/make.config

CFLAGS := $(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS := $(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS := $(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS := $(LIBS) $(KERNEL_ARCH_LIBS)

OBJS := $(KERNEL_ARCH_OBJS) kernel.o

CRTI_OBJ := $(ARCHDIR)/crti.o
CRTBEGIN_OBJ := $(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtbegin.o)
CRTEND_OBJ := $(shell $(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=crtend.o)
CRTN_OBJ := $(ARCHDIR)/crtn.o

OBJ_LINK_LIST := $(CRTI_OBJ) $(CRTBEGIN_OBJ) $(OBJS) $(CRTEND_OBJ) $(CRTN_OBJ)

.PHONY: all $(KERNEL) clean install install-headers install-kernel

all: $(KERNEL)

$(KERNEL): $(OBJ_LINK_LIST) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(OBJ_LINK_LIST) $(LDFLAGS) $(LIBS)

%.o: %.c
	$(CC) -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)

%.o: %.S
	$(CC) -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

clean:
	rm -f $(KERNEL) $(OBJS) $(CRTI_OBJ) $(OBJS) $(CRTN_OBJ)
	find . -type f -name "*.o" -delete

install: install-headers install-kernel

install-headers:
	mkdir -p $(SYSROOT)$(INCLUDEDIR)
	cp -RTv include $(SYSROOT)$(INCLUDEDIR)

install-kernel: $(KERNEL)
	mkdir -p $(SYSROOT)$(BOOTDIR)
	cp $(KERNEL) $(SYSROOT)$(BOOTDIR)
