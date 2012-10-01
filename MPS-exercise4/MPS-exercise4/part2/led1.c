#include <linux/init.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/ioport.h>
#include <asm/io.h>
MODULE_LICENSE("Dual BSD/GPL");

static int hello_init(void)
{
  
  volatile unsigned long *REG_GPIO6_OE;
  volatile unsigned long *REG_GPIO6_DOUT;
  
 
  if(request_mem_region(0x49058034, 12, "hello") == NULL) {
    printk("Allocation for I/O memmory range failed\n");
    return 0;
  }
  
  REG_GPIO6_OE = ioremap(0x49058034, 1);
  REG_GPIO6_DOUT = ioremap(0x4905803c, 1);
  
  iowrite32(ioread32(REG_GPIO6_OE) & ~(1<<26), REG_GPIO6_OE);
  
  iowrite32(ioread32(REG_GPIO6_DOUT) & ~(1<<26), REG_GPIO6_DOUT);
  
  
  printk(KERN_ALERT "Hello world!\n");
  return 0;
}

static int hello_exit(void)
{
  volatile unsigned long *REG_GPIO6_DOUT;
  
  REG_GPIO6_DOUT = ioremap(0x4905803c, 1);

  iowrite32(ioread32(REG_GPIO6_DOUT) | (1<<26), REG_GPIO6_DOUT);
  

  release_mem_region(0x49058034, 12);
  printk(KERN_ALERT "Goodbye world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

