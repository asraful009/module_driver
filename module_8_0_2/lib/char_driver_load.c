	
//Thu Jan  5 18:40:42 2012 


int p_init_driver(struct p_driver *pdriver)
{	

	int result_driver;
	
	if(pdriver->driver_major_number)
	{
		pdriver->dev=
			MKDEV(
				pdriver->driver_major_number, 
				pdriver->driver_minor_number
			);
		result_driver=
			register_chrdev_region
			(
				pdriver->dev,//driver_first_number,
				pdriver->limit,
				pdriver->driver_name
			);
	}
	else
	{
		result_driver=
			alloc_chrdev_region
			(
				&pdriver->dev,
				pdriver->driver_first_number,
				pdriver->limit, 
				pdriver->driver_name
			);
		
		pdriver->driver_major_number=
			MAJOR
			(
				pdriver->dev
			);
	
	}
	if(result_driver<0)
	{
		printk
		(
			KERN_WARNING "pdriver can not get major %d\n",
			pdriver->driver_major_number
		);
		return -1;
	}
				
					
	printk("<1>----%s driver device create by  p_init_driver on %d major=%d minor=%d. [ok]\n",
		pdriver->driver_name,
		pdriver->dev,
		MAJOR(pdriver->dev),
		MINOR(pdriver->dev)
		);
	
	
	
	
	return result_driver;

}

void p_rel_driver(struct p_driver *p_driver)
{
	int i;
	
	if(p_driver->dev)
	{
		for(i=0; i<p_driver->limit; i++)
		{
			
			{
				cdev_del(&p_driver->p_dev[i].cdev);
			}
			
		}
		kfree(p_driver->p_dev);
	}

	unregister_chrdev_region
	(
		p_driver->dev,
		p_driver->limit
	);
	
	printk("<1>----%s driver device release on %d. [ok]\n",
		p_driver->driver_name,
		p_driver->dev);
		
}


static void p_setup_cdev(struct p_driver *p_driver)
{
	int err, i;
	dev_t dev;
	
	p_driver->p_dev=kmalloc(p_driver->limit*sizeof(struct p_dev), GFP_KERNEL);
	
	if(p_driver->p_dev)
	{
		memset(p_driver->p_dev, 0, p_driver->limit*sizeof(struct p_dev));
	
		for(i=0; i<p_driver->limit; i++)
		{
	
			dev= MKDEV(
					p_driver->driver_major_number, 
					p_driver->driver_minor_number + i
				);
			printk
			(
				"<1>++++%s device p_setup-cdev on %d %d. [ok]\n",
					p_driver->driver_name,
					dev,
					i
			);
			
			cdev_init(&p_driver->p_dev[i].cdev, &p_driver->pfops);
			p_driver->p_dev[i].cdev.owner=THIS_MODULE;
			p_driver->p_dev[i].cdev.ops=&p_driver->pfops;
			err=cdev_add(&p_driver->p_dev[i].cdev, dev, 1);
	
			if(err)
				printk
				(
					"<1> Error %d adding \"%s\" in p_setup_cdev %d\n",
					err,
					p_driver->driver_name,
					p_driver->limit
				);
		
			printk
			(
				"<1> success %d adding i=%d\"%s\" in p_setup_cdev %d [ok]\n",
				err,
				i,
				p_driver->driver_name,
				p_driver->limit
			);
				
		}
			
	}
	
	
	
		
}



