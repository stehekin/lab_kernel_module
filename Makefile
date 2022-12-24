KDIR ?= /usr/src/linux

# Set FNAME_C to the kernel module name source filename (without .c)
FNAME_C := dummy_misc

PWD            := $(shell pwd)
obj-m          += ${FNAME_C}.o
EXTRA_CFLAGS   += -UDEBUG
#EXTRA_CFLAGS   += -DDEBUG

all:
	@echo
	@echo '--- Building : KDIR=${KDIR} ARCH=${ARCH} CROSS_COMPILE=${CROSS_COMPILE} EXTRA_CFLAGS=${EXTRA_CFLAGS} ---'
	@echo
	make -C $(KDIR) M=$(PWD) modules