#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/device.h>



#define DEVICE_NAME "rpifan"
#define CLASS_NAME "rpi"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Sebastian Ardelean");
MODULE_DESCRIPTION("A Linux Driver for fan controlling on RPi.");
MODULE_VERSION("0.1");


static int major_number;
static char message[256] = {0};
static short size_of_message;
static int number_opens = 0;
static struct class *rpifan_class = NULL;
static struct device *rpifan_device = NULL;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);


static struct file_operations fops =
  {
    .open = dev_open,
    .read = dev_read,
    .write = dev_write,
    .release = dev_release
  };


int dev_open(struct inode *inodep, struct file *filep) {
  return 0;
}

int dev_release(struct inode *inodep, struct file *filep) {
  return 0;
}

ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset) {
  return 0;
}

ssize_t dev_write(struct file *filep, const char *buffer, size_t len, loff_t *offset) {
  return 0;
}

static int __init rpifan_init(void) {
  int ret_code = 0;
  printk(KERN_INFO "RpiFan: Initializing\n");
  major_number = register_chrdev(0, DEVICE_NAME, &fops);
  if (major_number < 0) {
    printk(KERN_ALERT "RpiFan: Failed to register a major number\n");
    ret_code = major_number;
    goto error_return;
  }
  printk(KERN_INFO "RpiFan: Registered successfully with major number %d\n", major_number);

  rpifan_class = class_create(THIS_MODULE, CLASS_NAME);
  if (IS_ERR(rpifan_class)) {
    printk(KERN_ALERT "RpiFan: Failed to register device class\n");
    ret_code = PTR_ERR(rpifan_class);
    goto class_create_error;
  }

  printk(KERN_INFO "RpiFan: Device class registered successfully\n");

  rpifan_device = device_create(rpifan_class,
                                NULL,
                                MKDEV(major_number, 0),
                                NULL,
                                DEVICE_NAME);
   if (IS_ERR(rpifan_device)) {
    printk(KERN_ALERT "RpiFan: Failed to create the device\n");
    ret_code = PTR_ERR(rpifan_device);
    goto device_create_error;
  }

  printk(KERN_INFO "RpiFan: Device was initialized successfully\n");
  goto error_return;
 device_create_error:
  class_destroy(rpifan_class);  
 class_create_error:
  unregister_chrdev(major_number, DEVICE_NAME);  
 error_return:
  return ret_code;
}

static void __exit rpifan_exit(void) {
  // if (rpifan_class != NULL) {
    device_destroy(rpifan_class, MKDEV(major_number, 0));
    class_unregister(rpifan_class);
    class_destroy(rpifan_class);
    //}
  
  unregister_chrdev(major_number, DEVICE_NAME);
  printk(KERN_INFO "RpiFan: Goodbye! :(\n");
}


module_init(rpifan_init);
module_exit(rpifan_exit);


