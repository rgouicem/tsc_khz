KDIR ?= /lib/modules/$(shell uname -r)/build

obj-m  := tsc_khz.o

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
