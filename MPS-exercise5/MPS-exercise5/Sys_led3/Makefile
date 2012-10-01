ifeq ($(KERNELRELEASE),)
	# If we are NOT invoked from the
	# kernel build system
	KERNELDIR = ~/sources/linux-3.2.6
	PWD := $(shell pwd)

modules:
	$(MAKE) ARCH=arm CROSS_COMPILE=arm-angstrom-linux-gnueabi- -C $(KERNELDIR) M=$(PWD) modules

.PHONY: modules clean

else
	# called from kernel build system:
	# just declare what our modules are
	obj-m := sys_led3.o
endif

