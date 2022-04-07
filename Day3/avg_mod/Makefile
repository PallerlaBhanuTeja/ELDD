
        obj-m := avg.o ../add_mod/add.o

        KDIR = /lib/modules/$(shell uname -r)/build/

        PWD = $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf /lib/modules/$(shell uname -r)/extra/*

install:
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install
	depmod -a

