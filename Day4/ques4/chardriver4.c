//  Caluculator driver (character driver):add, sub, mul, div

// Initialisation functions
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("BHANU TEJA");

#define NAMEADD DeviceA
#define NAMESUB DeviceS
#define NAMEMUL DeviceM
#define NAMEDIV DeviceD

// Function Prototypes
int NAMEADD_open_add(struct inode *inode, struct file *filp);
int NAMEADD_release_add(struct inode *inode, struct file *filp);
ssize_t NAMEADD_write_add(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos);
ssize_t NAMEADD_read_add(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos);

int NAMESUB_open_sub(struct inode *inode, struct file *filp);
int NAMESUB_release_sub(struct inode *inode, struct file *filp);
ssize_t NAMESUB_write_sub(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos);
ssize_t NAMESUB_read_sub(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos);

int NAMEMUL_open_mul(struct inode *inode, struct file *filp);
int NAMEMUL_release_mul(struct inode *inode, struct file *filp);
ssize_t NAMEMUL_write_mul(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos);
ssize_t NAMEMUL_read_mul(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos);

int NAMEDIV_open_div(struct inode *inode, struct file *filp);
int NAMEDIV_release_div(struct inode *inode, struct file *filp);
ssize_t NAMEDIV_write_div(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos);
ssize_t NAMEDIV_read_div(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos);

// Structure that defines the operations provided by the driver
struct file_operations fopsa =
{
    .open = NAMEADD_open_add,
    .read = NAMEADD_read_add,
    .write = NAMEADD_write_add,
    .release = NAMEADD_release_add,
};

struct file_operations fopss =
{
    .open = NAMESUB_open_sub,
    .read = NAMESUB_read_sub,
    .write = NAMESUB_write_sub,
    .release = NAMESUB_release_sub,
};

struct file_operations fopsm =
{
    .open = NAMEMUL_open_mul,
    .read = NAMEMUL_read_mul,
    .write = NAMEMUL_write_mul,
    .release = NAMEMUL_release_mul,
};

struct file_operations fopsd =
{
    .open = NAMEDIV_open_div,
    .read = NAMEDIV_read_div,
    .write = NAMEDIV_write_div,
    .release = NAMEDIV_release_div,
};

// global variables
int sum = 0;
int sub = 0;
int mul = 1;
int div = 1;

// Structure for a character driver
struct cdev *cdeva;
struct cdev *cdevs;
struct cdev *cdevm;
struct cdev *cdevd;

// Init Module
static int __init CharDevice_init(void)
{
    int resulta, results, resultm, resultd;
    int MAJORa, MINORa, MAJORs, MINORs, MAJORm, MINORm, MAJORd, MINORd;
    dev_t DevNoa, DevNos, DevNom, DevNod;
    DevNoa = MKDEV(257, 0); // Statically creating a device number
    MAJORa = MAJOR(DevNoa);
    MINORa = MINOR(DevNoa);
    printk(KERN_ALERT "Device 1: The Major number is %d and the Minor number is %d.\n", MAJORa, MINORa);
    resulta = register_chrdev_region(DevNoa, 1, "DeviceA"); // register device region
    if(resulta < 0)
    {
        printk(KERN_ALERT "Requested region is not obtainable.\n");
        return (-1);
    }

    cdeva = cdev_alloc(); // allocate memory to char device structure
    cdeva->ops = &fopsa;   // link our file operations to the char device

    resulta = cdev_add(cdeva, DevNoa, 1); // Notify the kernel about the new device
    if(resulta < 0)
    {
        printk(KERN_ALERT "The char device has not been created.\n");
        unregister_chrdev_region(DevNoa, 1);
        return (-1);
    }

    DevNos = MKDEV(257, 1); // Statically creating a device number
    MAJORs = MAJOR(DevNos);
    MINORs = MINOR(DevNos);
    printk(KERN_ALERT "Device 2: The Major number is %d and the Minor number is %d.\n", MAJORs, MINORs);
    results = register_chrdev_region(DevNos, 1, "DeviceS"); // register device region
    if(results < 0)
    {
        printk(KERN_ALERT "Requested region is not obtainable.\n");
        return (-1);
    }

    cdevs = cdev_alloc(); // allocate memory to char device structure
    cdevs->ops = &fopss;   // link our file operations to the char device

    results = cdev_add(cdevs, DevNos, 1); // Notify the kernel about the new device
    if(results < 0)
    {
        printk(KERN_ALERT "The char device has not been created.\n");
        unregister_chrdev_region(DevNos, 1);
        return (-1);
    }

    DevNom = MKDEV(257, 2); // Statically creating a device number
    MAJORm = MAJOR(DevNom);
    MINORm = MINOR(DevNom);
    printk(KERN_ALERT "Device 3: The Major number is %d and the Minor number is %d.\n", MAJORm, MINORm);
    resultm = register_chrdev_region(DevNom, 1, "DeviceM"); // register device region
    if(resultm < 0)
    {
        printk(KERN_ALERT "Requested region is not obtainable.\n");
        return (-1);
    }

    cdevm = cdev_alloc(); // allocate memory to char device structure
    cdevm->ops = &fopsm;   // link our file operations to the char device

    resultm = cdev_add(cdevm, DevNom, 1); // Notify the kernel about the new device
    if(resultm < 0)
    {
        printk(KERN_ALERT "The char device has not been created.\n");
        unregister_chrdev_region(DevNom, 1);
        return (-1);
    }

    DevNod = MKDEV(257, 3); // Statically creating a device number
    MAJORd = MAJOR(DevNod);
    MINORd = MINOR(DevNod);
    printk(KERN_ALERT "Device 4: The Major number is %d and the Minor number is %d.\n", MAJORd, MINORd);
    resultd = register_chrdev_region(DevNod, 1, "DeviceD"); // register device region
    if(resultd < 0)
    {
        printk(KERN_ALERT "Requested region is not obtainable.\n");
        return (-1);
    }

    cdevd = cdev_alloc(); // allocate memory to char device structure
    cdevd->ops = &fopsd;   // link our file operations to the char device

    resultd = cdev_add(cdevd, DevNod, 1); // Notify the kernel about the new device
    if(resultd < 0)
    {
        printk(KERN_ALERT "The char device has not been created.\n");
        unregister_chrdev_region(DevNod, 1);
        return (-1);
    }
    return 0;
}

// Cleanup Module
void __exit CharDevice_exit(void)
{
    int MAJORa, MINORa, MAJORs, MINORs, MAJORm, MINORm, MAJORd, MINORd;
    dev_t DevNoa, DevNos, DevNom, DevNod;
    DevNoa = MKDEV(257, 0); // Statically creating a device number
    MAJORa = MAJOR(DevNoa);
    MINORa = MINOR(DevNoa);
    printk(KERN_ALERT "DEvice 1: The Major number is %d and the Minor number is %d.\n", MAJORa, MINORa);
    unregister_chrdev_region(DevNoa, 1); // unregister the device number and the device created
    cdev_del(cdeva);

    DevNos = MKDEV(257, 1); // Statically creating a device number
    MAJORs = MAJOR(DevNos);
    MINORs = MINOR(DevNos);
    printk(KERN_ALERT "Device 2: The Major number is %d and the Minor number is %d.\n", MAJORs, MINORs);
    unregister_chrdev_region(DevNos, 1); // unregister the device number and the device created
    cdev_del(cdevs);

    DevNom = MKDEV(257, 2); // Statically creating a device number
    MAJORm = MAJOR(DevNom);
    MINORm = MINOR(DevNom);
    printk(KERN_ALERT "Device 3: The Major number is %d and the Minor number is %d.\n", MAJORm, MINORm);
    unregister_chrdev_region(DevNom, 1); // unregister the device number and the device created
    cdev_del(cdevm);

    DevNod = MKDEV(257, 3); // Statically creating a device number
    MAJORd = MAJOR(DevNod);
    MINORd = MINOR(DevNod);
    printk(KERN_ALERT "DEvice 4: The Major number is %d and the Minor number is %d.\n", MAJORd, MINORd);
    unregister_chrdev_region(DevNod, 1); // unregister the device number and the device created
    cdev_del(cdevd);
    printk(KERN_ALERT "All the resources which were allocated have been unregistered.\n");
    return;
}

// open system call
int NAMEADD_open_add(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "Device 1: In kernel open system call has been executed.\n");
    return 0;
}

int NAMESUB_open_sub(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "Device 2: In kernel open system call has been executed.\n");
    return 0;
}

int NAMEMUL_open_mul(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "Device 3: In kernel open system call has been executed.\n");
    return 0;
}

int NAMEDIV_open_div(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "Device 4: In kernel open system call has been executed.\n");
    return 0;
}

// close system call
int NAMEADD_release_add(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "Device 1: In kernel release system call has been executed.\n");
    return 0;
}

int NAMESUB_release_sub(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "Device 2: In kernel release system call has been executed.\n");
    return 0;
}

int NAMEMUL_release_mul(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "Device 3: In kernel release system call has been executed.\n");
    return 0;
}

int NAMEDIV_release_div(struct inode *inode, struct file *filp)
{
    printk(KERN_ALERT "Device 4: In kernel release system call has been executed.\n");
    return 0;
}

// read functionality
ssize_t NAMEADD_read_add(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[50];
    sprintf(Kbuf, "%d", sum);
    sum = 0;
    printk("sum = %d\n", sum);
    unsigned long result;
    ssize_t retval;
    result = copy_to_user((char *)Ubuf, (char *)Kbuf, sizeof(Kbuf)); // copy data to user
    if(result == 0)
    {
        printk(KERN_ALERT "Data successfully read.\n");
        retval = count;
        return retval;
    }
    else if(result > 0)
    {
        printk(KERN_ALERT "Partial data read.\n");
        retval = (count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "Error writing data to user.\n");
        retval = -EFAULT;
        return retval;
    }
}

ssize_t NAMESUB_read_sub(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[50];
    sprintf(Kbuf, "%d", sub);
    sub = 0;
    printk("sub = %d\n", sub);
    unsigned long result;
    ssize_t retval;
    result = copy_to_user((char *)Ubuf, (char *)Kbuf, sizeof(Kbuf)); // copy data to user
    if(result == 0)
    {
        printk(KERN_ALERT "Data successfully read.\n");
        retval = count;
        return retval;
    }
    else if(result > 0)
    {
        printk(KERN_ALERT "Partial data read.\n");
        retval = (count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "Error writing data to user.\n");
        retval = -EFAULT;
        return retval;
    }
}

ssize_t NAMEMUL_read_mul(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[50];
    sprintf(Kbuf, "%d", mul);
    mul = 1;
    printk("mul = %d\n", mul);
    unsigned long result;
    ssize_t retval;
    result = copy_to_user((char *)Ubuf, (char *)Kbuf, sizeof(Kbuf)); // copy data to user
    if(result == 0)
    {
        printk(KERN_ALERT "Data successfully read.\n");
        retval = count;
        return retval;
    }
    else if(result > 0)
    {
        printk(KERN_ALERT "Partial data read.\n");
        retval = (count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "Error writing data to user.\n");
        retval = -EFAULT;
        return retval;
    }
}

ssize_t NAMEDIV_read_div(struct file *filp, char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[50];
    sprintf(Kbuf, "%d", div);
    div = 1;
    printk("div = %d\n", div);
    unsigned long result;
    ssize_t retval;
    result = copy_to_user((char *)Ubuf, (char *)Kbuf, sizeof(Kbuf)); // copy data to user
    if(result == 0)
    {
        printk(KERN_ALERT "Data successfully read.\n");
        retval = count;
        return retval;
    }
    else if(result > 0)
    {
        printk(KERN_ALERT "Partial data read.\n");
        retval = (count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "Error writing data to user.\n");
        retval = -EFAULT;
        return retval;
    }
}

// write functionality
ssize_t NAMEADD_write_add(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[80];
    int a;
    unsigned long result;
    ssize_t retval;
    result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data from user
    if(result == 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        sscanf(Kbuf, "%d", &a);
        sum = sum + a;
        printk("sum = %d", sum);
        printk(KERN_ALERT "Data successfully written.\n");
        retval = count;
        return retval;
    }
    else if(result > 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        printk(KERN_ALERT "Partial data written.\n");
        retval = (count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "Error writing data to kernel.\n");
        retval = -EFAULT;
        return retval;
    }
}

ssize_t NAMESUB_write_sub(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[80];
    int a;
    unsigned long result;
    ssize_t retval;
    result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data from user
    if(result == 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        sscanf(Kbuf, "%d", &a);
        if(sub == 0)
            sub = a;
        else
            sub = sub - a;
        printk("sub = %d", sub);
        printk(KERN_ALERT "Data successfully written.\n");
        retval = count;
        return retval;
    }
    else if(result > 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        printk(KERN_ALERT "Partial data written.\n");
        retval = (count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "Error writing data to kernel.\n");
        retval = -EFAULT;
        return retval;
    }
}

ssize_t NAMEMUL_write_mul(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[80];
    int a;
    unsigned long result;
    ssize_t retval;
    // strcpy(Kbuf, Ubuf);
    result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data from user
    if(result == 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        sscanf(Kbuf, "%d", &a);
        mul = mul * a;
        printk("mul = %d", mul);
        printk(KERN_ALERT "Data successfully written.\n");
        retval = count;
        return retval;
    }
    else if(result > 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        printk(KERN_ALERT "Partial data written.\n");
        retval = (count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "Error writing data to kernel.\n");
        retval = -EFAULT;
        return retval;
    }
}

ssize_t NAMEDIV_write_div(struct file *filp, const char __user *Ubuf, size_t count, loff_t *f_pos)
{
    char Kbuf[80];
    int a;
    unsigned long result;
    ssize_t retval;
    // strcpy(Kbuf, Ubuf);
    result = copy_from_user((char *)Kbuf, (char *)Ubuf, count); // copy data from user
    if(result == 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        sscanf(Kbuf, "%d", &a);
        if(div == 1)
            div = a;
        else
            div = div / a;
        printk("div = %d", div);
        printk(KERN_ALERT "Data successfully written.\n");
        retval = count;
        return retval;
    }
    else if(result > 0)
    {
        printk(KERN_ALERT "Message from the user:  \n'%s'\n", Kbuf);
        printk(KERN_ALERT "Partial data written.\n");
        retval = (count-result);
        return retval;
    }
    else
    {
        printk(KERN_ALERT "Error writing data to kernel.\n");
        retval = -EFAULT;
        return retval;
    }
}

// Module over ride functions
module_init(CharDevice_init);
module_exit(CharDevice_exit);
