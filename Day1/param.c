#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Module Parameter passing example");
MODULE_AUTHOR("BHANU TEJA");

static char* charvar = "CDAC";
static int intvar = 10;

module_param(charvar,charp,S_IRUGO);
module_param(intvar,int,S_IRUGO);

static int param_init(void)
{
	printk(KERN_ALERT "\n The value of charvar is %s\n",charvar);
	return 0;
}

static void param_exit(void)
{
	printk(KERN_ALERT "\n Exit of Module\n");
}

module_init(param_init);
module_exit(param_exit);

