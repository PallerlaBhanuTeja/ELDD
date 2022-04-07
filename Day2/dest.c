#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include "kern_add.h"

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Export symbol Example");

static int one = 1;
static int two = 2;

static int avg_init(void)
{
	printk(KERN_ALERT "\n Average is Calculated\n");
	printk(KERN_ALERT "\n Average Result: %d\n", my_add(one,two)/2);
	return 0;
}

static void avg_exit(void)
{
	printk(KERN_ALERT "\nAverage Module End");
}

module_init(avg_init);
module_exit(avg_exit);
