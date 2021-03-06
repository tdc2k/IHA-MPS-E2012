/*                                                     
 * ID: bootkey.c 
 */                                                    
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <linux/module.h>

#define MYGPIO_MAJOR  65
#define MYGPIO_MINOR   0
#define MYGPIO_CHS     1
#define MAXLEN       512


static struct cdev MyGpioDev;
struct file_operations mygpio_Fops;

static int devno;

const unsigned int gpio_len = 1;
struct gpioPort{
  unsigned int num;
  enum direnu { in, out } dir;
  const char label[10]; // Very important to specify a size. Just [] causes havoc to gpio indexing
} gpio[] = {
  {7, in, "BOOT_KEY"}
};


static int mygpio_init(void)
{
	int err; 
    
	printk(KERN_ALERT "MyGPIO BOOT_KEY Module Inserting\n");
  
	/*
	* Request GPIO Ressources
	*/
	int i;
	for(i = 0; i < gpio_len; i++)
	{	
		if ((err = gpio_request(gpio[i].num, gpio[i].label)) < 0)
       		{
            		printk (KERN_ALERT "Error %d requesting %s ressource\n", err, gpio[i].label);
            		return err;
		}
		printk (KERN_ALERT "GPIO %s ressource\n", gpio[i].label);
	}
	
			
	/*
	* Set GPIO Direction
	*/
	for( i = 0; i < gpio_len; i++)
	{
		if (gpio[i].dir == in)
        	{
	    		if ((err = gpio_direction_input(gpio[i].num)) < 0)
	    		{
	        		printk (KERN_ALERT "Error %d setting %s as input\n", err, gpio[i].label);
                		return err;
	    		}
			printk (KERN_ALERT "GPIO DIRECTION %s as input\n", gpio[i].label);	
        	}
        	else
        	{ 
            		if ((err = gpio_direction_output(gpio[i].num, 0)) < 0)
	   		{
	        		printk (KERN_ALERT "Error %d setting %s as output\n", err, gpio[i].label);
                		return err;
	    		}
			printk (KERN_ALERT "GPIO DIRECTION %s as output\n", gpio[i].label);	
        	}
	}
	
	/*
	* Allocate Major/Minor Numbers 
	*/
	devno = MKDEV(MYGPIO_MAJOR, MYGPIO_MINOR);
	if((err=register_chrdev_region(devno, gpio_len, "myGpio"))<0)
	{
		printk(KERN_ALERT "Can't Register Major no: %i\n", MYGPIO_MAJOR);
		return err;
	}


	/*
	* Create cdev
	*/       
	cdev_init(&MyGpioDev, &mygpio_Fops);
	err = cdev_add(&MyGpioDev, devno, gpio_len);
	if (err) 
	{
		printk (KERN_ALERT "Error %d adding MyGpio device\n", err);
	        return -1;
	}

	
    return 0;
}

static void mygpio_exit(void)
{
	int i;
	printk(KERN_NOTICE "Removing MyGPIO BOOT_KEY Module\n");
	
	/*
	* Delete cdev and unregister device
	*/
	unregister_chrdev_region(devno, gpio_len);
	cdev_del(&MyGpioDev);

    	/*
     	* Free GPIO Ressources 
     	*/
    	for(i = 0; i < gpio_len; i++)
		gpio_free(gpio[i].num);   
}


int mygpio_open(struct inode *inode, struct file *filep)
{
    int major, minor;

    major = MAJOR(inode->i_rdev);
    minor = MINOR(inode->i_rdev);

    printk("Opening MyGpio Device [major], [minor]: %i, %i\n", major, minor);

    /*
     *  Try to get the module semaphore
     */
    if (!try_module_get(mygpio_Fops.owner))
      return -ENODEV;

    return 0;
}

int mygpio_release(struct inode *inode, struct file *filep)
{
    int minor, major;
    
    major = MAJOR(inode->i_rdev);
    minor = MINOR(inode->i_rdev);

    printk("Closing MyGpio Device [major], [minor]: %i, %i\n", major, minor);

    /*
     * Put the module semaphore
     * to release it
     */
    module_put(mygpio_Fops.owner);
    
    return 0;
}

ssize_t mygpio_read(struct file *filep, char __user *buf, size_t count, loff_t *f_pos)
{
	char readBuf[MAXLEN];
	int len, result=-1, minor;

	/*
	* retrieve minor from file ptr
	*/
	minor = MINOR(filep->f_dentry->d_inode->i_rdev);
	printk(KERN_ALERT "Reading from MyGpio [Minor] %i \n", minor);

	/*
	* Read GPIO port
	*/
	result = gpio_get_value(gpio[minor].num);
		
	/*
	* Convert int to string
	* using sprintf
	*/
	len=sprintf(readBuf,"%i", result);
	len++; // To include null-termination

	printk(KERN_ALERT "testBuf: %s \n", readBuf);

	/*
	* Copy string result
	* to User Space
	*/
	if(copy_to_user(buf, readBuf, len))
		return -EFAULT;

    *f_pos += len;
    return len;    
}


struct file_operations mygpio_Fops = 
{
    .owner   = THIS_MODULE,
    .open    = mygpio_open,
    .release = mygpio_release,
    .read    = mygpio_read,
};

module_init(mygpio_init);
module_exit(mygpio_exit);

MODULE_DESCRIPTION("My GPIO BOOT_KEY Module");
MODULE_AUTHOR("GTLT-MPS.blogspot.dk <http://www.iha.dk>");
MODULE_LICENSE("GPL");

