// simple hello world program


#include<linux/init.h>
#include<linux/module.h>

static int hello_init(void)
{
	printk(KERN_ALERT "\n Entrance of Module\n");	
	printk(KERN_ALERT "\n Hello World\n");
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "\n End of Module\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("BHANU TEJA");
MODULE_DESCRIPTION("This is a Simple Hello World Module");

