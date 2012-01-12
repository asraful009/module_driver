


//sun Jan  8 14:11:10 PM 2012 BDT

#include <stdio.h>
#include <malloc.h>

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




int main(int argc, char *argv[])
{
	unsigned int i,k;
	unsigned char j[5];
	
;
	unsigned char uc='\0';
   	unsigned long long int ui, uj, pid=160L,thr=124L;
	
	unsigned char message[100],*pc;//=(char *)malloc(sizeof(char)*100);
	
	pc=message;
	
	// j= (most)00100110(38) 00010001(17) 00001101(13) 00010010(18)(lest) =638651666	4-bytes
	
	j[0]=18;
	j[1]=13;
	j[2]=17;
	j[3]=38;
	j[4]='\0'; //end string not need
	
//	i=*(typeof(j) *)(&j);

	p_assign(i,j);
	
	
	//p_assign(message, pid);
	pid=1;
while(pid!=0)
{
	pid=0;
	p_assign_position(message, 0, pid);

	scanf("%llu %llu", &pid, &thr);	
	p_assign_position(message, 0, pid);
	for(i=7;(int)i>=0;i--)
		{
			printf(" %d =%d %p \n", i, message[i], &message[i]);
			
			
		}
		printf("pid==========\n");
	p_assign_position(message, sizeof(unsigned long long int), thr);

for(i=15;(int)i>=8;i--)
		{
			printf(" %d =%d %p\n", i, message[i], &message[i]);
			
			
		}
		printf("thr==========\n");
//	p_assign_position(uj, sizeof(unsigned long long int), message);

///	p_assign_position(message, sizeof(unsigned long long int)*2+sizeof(unsigned int), uc);
	p_assign(ui, message);
	p_assign_str_pos(uj, message, sizeof(typeof(thr)));

	printf
		(
			"print_message function \"%llu\" %llu %llu %d %p %p %p\n", 
			*(typeof(pid ) *)(&message),
			ui,
			uj,
			sizeof(void),
			&message,
			pc+(0x0001)*8,
			message+((0x0001)*sizeof(unsigned long long int))
			
		);
		for(i=15;(int)i>=0;i--)
		{
			printf(" %d =%d %p\n", i, message[i], &message[i]);
			
			
		}
		printf("\n");

}	
	printf("%u %u\n",i ,*(unsigned int *)&j);

	//free(message);

	return 0;
}


