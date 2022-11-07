#include "threads1.h"


void* routine1()
{
	printf("Hello there \n");
	sleep(2);
	printf("Bye there! \n");
}

void* routine2()
{
	printf("Hei !\n");
	sleep(2);
	printf("Vi sees \n!");
}

int main(void)
{
	pthread_t t1;
	pthread_t t2;
	
	//check if thread was successful created
	if(pthread_create(&t1,NULL,&routine1,NULL) != 0)
	{
		printf("pthread creation error");
		return 1;
	}
	pthread_join(t1,NULL);

	if(pthread_create(&t2,NULL,&routine2,NULL) != 0)
	{
		printf("pthread creation error");
		return 1;
	}
	pthread_join(t2,NULL);
	
	return 0;	
}