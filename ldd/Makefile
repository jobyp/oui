ifneq ($(KERNELRELEASE),)

obj-m := hello.o

else

KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

.PHONY: all
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

.PHONY: clean
clean:
	@rm -f *~ *.o *.ko *.mod.c *.order *.symvers

endif
