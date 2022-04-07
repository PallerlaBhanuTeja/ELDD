#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("BHANU TEJA");
MODULE_DESCRIPTION("Export Symbol Example");

static int my_add(int a, int b)
{
	return (a + b);
}

// Command to export symbol into kernel symbol table

EXPORT_SYMBOL_GPL(my_add);

static int add_init(void)
{
	printk(KERN_ALERT "\n Initialization of Module\n");
	return 0;
}

static void add_exit(void)
{
	printk(KERN_ALERT "\n Clean up of Module");
}

module_init(add_init);
module_exit(add_exit);
