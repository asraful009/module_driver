

//Thu Jan  5 18:40:27 2012 

#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/slab.h>

#ifndef P_DRIVER_H
#define P_DRIVER_H

#define p_DATA_SIZE 100


struct p_block_data
{
	unsigned int length;
	char *data;
};


struct p_block
{
	unsigned long long int p_id;		//8 bytes
	unsigned long long int thd_id;	//8 bytes
	unsigned int oparation;		//4-bytea
	
	
	struct p_block_data data;
	/////////////////////////////////
	///future facility
	unsigned long long int read_pos;
	unsigned long long int write_pos;
	
	
	///////////////////////////////
	
	
	struct p_block *next;
	

};



struct p_block *p_block_create();
int p_block_insert(struct p_block *, struct p_block *);
int p_block_delete(struct p_block *, struct p_block *);


struct p_dev
{
	struct p_block *data;
	int quantum;		/* the current quantum size */
	int qset;		/* the current array size */
	unsigned long size;
	//devfs_handle_t handle; 	/* only used if devfs is there */
	unsigned int access_key;/* used by sculluid and scullpriv */
	struct semaphore sem; 	/* mutual exclusion semaphore */
	struct cdev cdev;
	
};


typedef struct p_driver
{
	dev_t dev;
	dev_t driver_major_number; //unsigned int -> __u32 in 32bit OS maybe
	dev_t driver_first_number;
	dev_t driver_minor_number;
	char *driver_name;
	struct file_operations pfops;
	struct p_dev *p_dev;
	int limit;

}p_driver;


int p_driver_open(struct inode *, struct file *);


int p_init_driver(struct p_driver *);
void p_rel_driver(struct p_driver *);

static void p_setup_cdev(struct p_driver *);


int p_fop_open(struct inode *, struct file *);
int p_fop_release(struct inode *, struct file *);
ssize_t p_fop_read(struct file *, char __user *, size_t , loff_t *);
ssize_t p_fop_write(struct file *, const char __user *, size_t , loff_t *);


#include "block_oparation.c"
#include "char_driver_load.c"
#include "file_operations_func.c"



#endif

