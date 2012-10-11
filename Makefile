# Simple Makefile to build launcher_driver.ko and launcher_control
# Nick Glynn <Nick.Glynn@feabhas.com>
#

obj-m += launcher_driver.o
KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)

CC := $(CROSS_COMPILE)gcc
BIN := launcher_control
OBJECTS += $(BIN).c

all:
	$(MAKE) -C $(KDIR) M=${shell pwd} modules
	$(CC) $(OBJECTS) -o $(BIN)
	
clean:
	-$(MAKE) -C $(KDIR) M=${shell pwd} clean || true
	-rm $(BIN) || true
	-rm *.o *.ko *.mod.{c,o} modules.order Module.symvers || true

