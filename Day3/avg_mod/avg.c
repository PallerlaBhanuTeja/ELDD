#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include "kern_add.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Modprobe Example");

static int one = 2;
static int two = 4;

static int avg_init(void)
{
	printk(KERN_ALERT "\n Average Result: %d\n", my_add(one, two)/2);
	return 0;
}

static void avg_exit(void)
{
	printk(KERN_ALERT "\n Exit of Average Module\n");
}

module_init(avg_init);
module_exit(avg_exit);
