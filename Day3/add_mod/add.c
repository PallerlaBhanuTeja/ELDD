#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("BHANU TEJA");
MODULE_DESCRIPTION("Modprobe Example");

int my_add(int a, int b)
{
	return (a + b);
}

EXPORT_SYMBOL(my_add);

static int add_init(void)
{
	printk(KERN_ALERT "\n Initialisation of Module\n");
	return 0;
}

static void add_exit(void)
{
	printk(KERN_ALERT "\n Exit of Module\n");
}

module_init(add_init);
module_exit(add_exit);

