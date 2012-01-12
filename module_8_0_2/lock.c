


//Thu Jan  5 18:44:12 2012 BDT 


#include <linux/kernel.h> 
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h> 	///kmalloc()
#include <linux/fcntl.h>	///O_ACCMODE
#include <asm/uaccess.h>	///copy_to/from_user() function
#include <asm/io.h>		///inb() outb()
#include <linux/ioport.h>
#include <linux/string.h>	///string ... function strlen()
#include <linux/moduleparam.h>	///parameter




MODULE_LICENSE("DUAL BSD/GPL");
MODULE_AUTHOR("pavel");
MODULE_DESCRIPTION("now i have to lock the all ফাজলেমো of processes and pthreads he he !!! >>754 lines<<");

static int __init p_init(void);
static void __exit p_exit(void);



int p_lock_write;
int p_lock_read;

#include "lib/driver.h"




struct p_driver pdriver=
{
	driver_major_number: 	0,
	driver_name: 		"lock",
	limit:			1,
	driver_first_number: 	0,//both are same driver_first_number 
	driver_minor_number: 	0,//and driver_minor_number
	
	pfops:
	{
		owner:		THIS_MODULE,	///this have some talk
		open:		p_fop_open,
		release:	p_fop_release,
		read:		p_fop_read,
		write:		p_fop_write
			
	}
};

int limit;
char *driver_name;

module_param(limit, int, 0);
MODULE_PARM_DESC(limit, "Driver create number (int)");
module_param(driver_name, charp, 0);
MODULE_PARM_DESC(driver_name, "Driver name (string)");



char *tmp;


static int __init p_init(void)
{
	
	int i;
	p_lock_write=0;
	p_lock_read=0;
	
	pdriver.limit=limit;
	pdriver.driver_name=driver_name;
	
	printk
	(
		"<1>pavel %s: loaded [ok]\n\n%d %d %s\n",
			pdriver.driver_name,
			pdriver.limit,
			pdriver.driver_first_number,
			pdriver.driver_name
	);
	
	
		
	if(p_init_driver(&pdriver)==0)
	{
		p_setup_cdev(&pdriver);
			
		printk
		(	KERN_ALERT "%s create %d %d\n",
				pdriver.driver_name,
				MAJOR(pdriver.dev),
				MINOR(pdriver.dev)
		);
	}
	else
		printk(KERN_ALERT "%s create error\n", pdriver.driver_name);	
	
	tmp=(char *)kmalloc(sizeof(char)*1024, GFP_KERNEL);
	if(tmp==NULL)
	{
		printk("<1> Error tmp allocation\n");
		return 0;
	}
	
	return 0;
}

static void __exit p_exit()
{

	if(tmp!=NULL)
		kfree(tmp);
		
		
	p_rel_driver(&pdriver);
	
	printk("<1>pavel %s: exit [ok]\n", pdriver.driver_name);
	
	
}

module_init(p_init);
module_exit(p_exit);




