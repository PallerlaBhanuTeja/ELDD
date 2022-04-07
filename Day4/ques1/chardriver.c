// Basic character driver program with open and close functionalities
// Initialisation Functions
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>

#define MYDEV MyCharDevice2

// Function Prototypes
int MYDEV_open(struct inode *inode, struct file *filp);
int MYDEV_release(struct inode *inode, struct file *filp);
ssize_t MYDEV_write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp);
ssize_t MYDEV_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);
//int MYDEV_flush (struct file *filp);

//Below structure define the operations that are provided by driver
struct file_operations fops =
{
        .owner   = THIS_MODULE,
        .open    = MYDEV_open,
        .release = MYDEV_release,
};

//Structure of character driver
struct cdev *my_cdev;


//Init Module
static int __init CharDevice_init(void)
{
        int result;
        int MAJOR,MINOR;
        dev_t Mydevno;
        Mydevno = MKDEV(255,0); // Creating a device number
        MAJOR = MAJOR(Mydevno);
        MINOR = MINOR(Mydevno);
        printk("\n Major Number is : %d.. Minor Number is : %d\n", MAJOR,MINOR);
        result = register_chrdev_region(Mydevno, 1, "MyCharDevice"); // Static registration(static allocation of major, minor no.)  of Device 
        if(result<0)
        {
                printk(KERN_ALERT "\n The region requested for is unavailable\n");
                return(-1);
        }

        my_cdev = cdev_alloc(); // Memory allocation to Character Device structure
        my_cdev->ops = &fops; // Link our file operations to Char device

        result = cdev_add(my_cdev,Mydevno,1); // Notifying the Kernel about new char Device
        if(result<0)
        {
                printk(KERN_ALERT "\n The char device has not been created\n");
                unregister_chrdev_region(Mydevno, 1);
        }
        return 0;
}

// Cleanup Module
void __exit CharDevice_exit(void)
{
        dev_t Mydevno;
        int MAJOR, MINOR;
        Mydevno = MKDEV(255,0);
        MAJOR = MAJOR(Mydevno);
        MINOR = MINOR(Mydevno);
        printk("\n The Major No. is : %d .. The Minor No. is: %d\n", MAJOR,MINOR);
        unregister_chrdev_region(Mydevno, 1); // Unregister the device numbers and devices created
        cdev_del(my_cdev);
        printk(KERN_ALERT "\n Device is unregistered...Bye\n");
        return;
}


//Open System Call
int MYDEV_open(struct inode *inode, struct file *filp)
{
        printk(KERN_ALERT "\n This is the Kernel.. Open Call...\n");
        return 0;
}

//Close System Call
int MYDEV_release(struct inode *inode, struct file *filp)
{
        printk(KERN_ALERT "\n This is the release call..Exit of My character Driver\n");
        return 0;
}

int Mydevno_flush (struct file *filp)
{
	printk(KERN_ALERT "\n This is the close function of the file\n");
	return 0;
}

// Module Over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);
