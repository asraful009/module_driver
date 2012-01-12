

//Fri Jan  6 21:01:15 2012 BDT
//by pavel
//for data insert, delete, ......
////////////////////////////////


//i fix real locking system now i just lock read and write method by value
//not use advance method while i want to implement 
//the method is out netwoking data comunication 


// send client "hi" -> server
//server open for read "OK"-> client
//client "<data>" -> server
//server "receive success" -> client
//cilent close() -> server
//server "bye" close() -> client




///////////////////////////////////

//struct p_block *head=NULL;


#define p_assign(assign, value) 			\
	({						\
		assign=*(typeof(assign ) *)(&value);	\
	})


#define p_assign_str_pos(assign, value, length) 			\
	({						\
		assign=*(typeof(assign ) *)((value)+(0x0001)*(size_t)length);	\
	})


#define p_assign_position(assign, position, value)	\
	({						\
		*(typeof(value ) *)(char *)((assign)+(0x0001)*position)=*(typeof(value ) *)(&value);	\
	})

#define p_assign_position_ptr(assign, position, ptr, type)	\
	({						\
		*(typeof(type ))(char *)((assign)+(0x0001)*position)=*(typeof(type )  *)(ptr);	\
	})


unsigned int p_strcpy(char *a, char *b)
{
	unsigned int i;
	
	for(i=0; b[i]!='\0'; i++)
	{
		a[i]=b[i];
	}
	a[i]='\0';
	
	return i;

}

struct p_block *p_block_create()
{
	struct p_block *temp=NULL;
	
	temp=(struct p_block *)kmalloc(sizeof(struct p_block)*1, GFP_KERNEL);
	
	if(temp==NULL)
		return NULL;
		
	temp->data.data=(char *)kmalloc(sizeof(char)*p_DATA_SIZE, GFP_KERNEL);
	
	if(temp->data.data==NULL)
		return NULL;
	
	
	return 0;
	

}

int p_set_p_block_by_string(struct p_block *tmp_block, const char *buf)
{

	tmp_block->p_id= *(unsigned long long int *)(buf+0);	
	tmp_block->thd_id=*(unsigned long long int *)(buf+8);
	tmp_block->oparation=*(unsigned int *)(buf+16);
	tmp_block->data.length=*(unsigned int *)(buf+20);
	
	if(tmp_block->data.length!=0)
	{
		tmp_block->data.data=(char *)kmalloc(sizeof(char)*tmp_block->data.length, GFP_KERNEL);
		p_strcpy(tmp_block->data.data, buf+24);
	}
	

	return 0;
}

int p_insert_new(struct p_block *start, struct p_block *block)
{
	
	struct p_block *temp;
	
	temp=start;
	
	while(temp!=NULL)
	{
		temp=temp->next;
	}
	
	temp->next=block;
	block->next=NULL;	
	
	

	return 0;
}

int p_lock_add(struct p_block *block)
{

	struct p_block *new;
	
	new=p_block_create();
	//p_insert_new();<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<,
	
	

}

struct p_lock *p_lock_search_pid_thr_op(struct p_block *start, unsigned long long int pid, unsigned long long int thr, unsigned int op)
{

	while(start!=NULL && !(start->p_id==pid && start->thd_id==thr && start->oparation==op))
	{
		start=start->next;
	}
	
	if((start->p_id!=pid || start->thd_id!=thr || start->oparation!=op))
	{
		return NULL;
	}
	
	return start;
	
}


int p_delete(struct p_block *start, struct p_block *block)
{
	
	struct p_block *temp, *t;
	
	temp=start;
	
	while(temp!=NULL && temp!=block)
	{
		t=temp;
		temp=temp->next;
	}
	
	if(temp==block)
	{
		if(temp->next==NULL)
		{
			kfree(temp);
			t->next=NULL;
		}
		else
		{
			t->next=temp->next;
			kfree(temp);
		}
	
	}
	else
	{
		return -2;///block not find
	}
	
	
	
	return 0;
}





