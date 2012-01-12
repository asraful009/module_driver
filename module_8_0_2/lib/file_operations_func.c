
//Mon Dec 05 09:12:33 BDT 2011 

#include <linux/fs.h>




int p_fop_open(struct inode *inode, struct file *filp)
{
	
	
	
	
	printk
	(
		"<1>	-->> major number %d and minor is %d\n",
		MAJOR(inode->i_rdev),
		MINOR(inode->i_rdev)
		
	);
	
	
	return 0;
	
}


int p_fop_release(struct inode *inode, struct file *filp)
{

	printk
	(
		"<1>	-->> %d %d want to bye \n",
		MAJOR(inode->i_rdev),
		MINOR(inode->i_rdev)
	);
	
	return 0;
}


ssize_t p_fop_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{


	if(p_lock_read==1)
		return 0;
	
	
	p_lock_read=1;
	
	printk
	(
		"<1>	>> want to read \n"
		
	);
	
	//if(pcount<=p_strlen)
	
	//	return 1;
	
	p_lock_read=0;
	
	return 0;
}

ssize_t p_fop_write(struct file *filp, const char __user *buf, size_t count,loff_t *f_pos)
{
	
	
	
	if(p_lock_write==1)
		return 0;
	
	
	struct p_block tmp_block;
	p_lock_write=1;
	
	printk
	(
		"<1>	%llu-->> want to write\n", *(unsigned long long int *)(buf+8)
	);
	
	
	
	
	p_set_p_block_by_string(&tmp_block, buf);
	
	printk
		(
			">>> %llu %llu %u %u %s<<<<<<\n",
			tmp_block.p_id,
			tmp_block.thd_id,
			tmp_block.oparation,
			tmp_block.data.length,
			tmp_block.data.data
		);

	kfree(tmp_block.data.data);
  	//copy_from_user(tmp, buf, count);
  	
  	//tmp[count]='\0';
  	
  	//printk("<1>-%s-\n", tmp);
  	
  	p_lock_write=0;
  	
  	return count;
	
	
	
}




