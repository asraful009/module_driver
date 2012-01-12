

//Tue Jan  3 05:20:24 2012 


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <time.h>	//nanosleep()
#include <unistd.h>	//usleep()
#include <sys/types.h>

#define size 50


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

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

void *print_message_function( void *ptr );
void *p_read(char *argv);
void *p_write(char *argv, char *a, int );

int  iret[size] ,i;

struct timespec s;

unsigned long long int pid;


int main()
{

	
	pthread_t thread[size];
	char message1[100][100];
	
	int  iret[size] ,i;
	
    	/* Create independent threads each of which will execute function */

	
	
	s.tv_sec = 0;
	s.tv_nsec = 5L;
	pid=getpid();
	
	for(i=0; i<size; i++)
	{
		//sprintf(message1[i], "number_%d", i);
		
		
		
		iret[i] = pthread_create( 
						&thread[i],
						NULL,
						print_message_function,
						(void*) message1[i]
					);
		
		//printf("iret %d\n", iret[i]);
		
	}

     	

	for(i=0; i<size; i++)
	{
		pthread_join( thread[i], NULL);
		//printf("iret %d\n", iret[i]);
	}

	//for(i=0; i<size; i++)
	//	printf("Thread %d returns: %d\n", i, iret[i]);
	
     	//exit(0);
     
	return 0;
	
}

void *print_message_function( void *ptr)
{

	char *message;
   
   	
   	int i, al;
	unsigned int op=12, length;
	char uc[20]="hi pavel u r well";
   	unsigned long long int thr=pthread_self();
	//pthread_mutex_lock( &mutex1 ); //for "race condition" no mutex condition
   
   		//sleep(1);
	length=strlen(uc);
		message = (char *) ptr;

		
		p_assign_position(message, 0, pid);
		p_assign_position(message, sizeof(unsigned long long int), thr);
		p_assign_position(message, sizeof(unsigned long long int)*2, op);
		p_assign_position(message, sizeof(unsigned long long int)*2 +sizeof(unsigned int), length);
		
		strcpy
			(
				message+
				sizeof(unsigned long long int)*2+sizeof(unsigned int)*2,
				uc
			);
		
		printf
			(
				">>%llu %llu %u %u %s<<\n",
				pid,
				thr,
				op,
				length,
				uc
			);
		
		
		
		al=sizeof(unsigned long long int)*2+sizeof(unsigned int)*2+length+1;
		p_write("/dev/lock0", message, al);
		usleep(1);
     		
	//pthread_mutex_unlock( &mutex1 );	//for "race condition"
	
	pthread_exit(0);
	printf("exit pthread \"%s\"------------\n", message);
}


void *p_read(char *argv)
{

	char a[100];
	FILE *fl;

	printf("\n");

	printf("Open node %s for read\n", argv);
				
	fl=fopen(argv, "rb");
	printf("start read ID %lu\n", pthread_self());
	fgets(a, sizeof(char)*10, fl);
	
	printf("-------\"%s\"-----%lu----\n", a, pthread_self());
	
	
	fclose(fl);
	printf("\n");

}


void *p_write(char *argv, char *a, int length)
{

	
	FILE *fl;
	int i=0;

	printf("\n");

	printf("Open node %s for write\n", argv);
	
	fl=fopen(argv, "wb");
	//scanf("%s", a);
	
	//printf("start write ID %lu message \"%s\"\n", pthread_self(), a);
	//while(strlen(a)>=i)
	{
	
		printf("start wr %d \n",length);
		nanosleep(&s, NULL);
		fwrite(a, sizeof(char), length, fl);
		printf("start wrddddddddd\n");
		//printf("read %d ID %lu\n", a[i], pthread_self());
		i++;
	}

	fclose(fl);
	printf("\n");
	
}



