#include <linux/init.h>
#include <linux/module.h>
#include <linux/miscdevice.h>
#include <linux/slab.h>		
#include <linux/mm.h>		
#include <linux/fs.h>		
#include <linux/sched.h>

#define MODNAME "dummy_misc"
MODULE_AUTHOR("qiang");
MODULE_DESCRIPTION("dummy misc device");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.1");

static int open_dummy(struct inode *inode, struct file *filp) {
    return nonseekable_open(inode, filp);
}

static ssize_t read_dummy(struct file *filp, char __user *ubuf, size_t count, loff_t *off) {
    return 1;
}

static ssize_t write_dummy(struct file *filp, const char __user *ubuf, size_t count, loff_t *off) {
    return 1;
}

static int close_dummy(struct inode *inode, struct file *filp) {
    return 0;
}

static const struct file_operations dummy_fops = {
    .open = open_dummy,
    .read = read_dummy,
    .write = write_dummy,
    .llseek = no_llseek,
    .release = close_dummy,
};

static struct miscdevice dummy_misc_dev = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = MODNAME,
    .mode = 0666,
    .fops = &dummy_fops,
};

static int __init dummy_init(void) {
    int ret = misc_register(&dummy_misc_dev);
    if (ret) {
        return ret;
    }
    return 0;
}

static void __exit dummy_exit(void) {
    misc_deregister(&dummy_misc_dev);
}

module_init(dummy_init);
module_exit(dummy_exit);
