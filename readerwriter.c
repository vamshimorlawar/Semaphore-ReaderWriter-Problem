#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex,writeb;
int data=0,rcount=0;

void *reader(void *arg)
{
	int f;
	f=((int)arg);
	
	sem_wait(&mutex);
	
	rcount=rcount+1;
	if(rcount==1)
		sem_wait(&writeb);
	
	sem_post(&mutex);
	
	printf("The data read by the reader %d is %d \n",f,data);
	
	sem_wait(&mutex);
	
	rcount=rcount-1;
	
	if(rcount==0)
		sem_post(&writeb);
	
	sem_post(&mutex);
}
void *writer(void *arg)
{
	int f;
	f=((int)arg);
	sem_wait(&writeb);
	data++;
	printf("The data read by the writer %d is %d \n",f,data);
	sem_post(&writeb);
	
}
int main()
{
	int i;
	
	pthread_t rtid[5],wtid[5];
	
	sem_init(&writeb,0,1);
	sem_init(&mutex,0,1);
	
	for(i=0;i<=2;i++)
	{
		pthread_create(&wtid[i],NULL,writer,(void *)i);
		pthread_create(&rtid[i],NULL,reader,(void *)i);
	
	}
	
	for(i=0;i<=2;i++)
	{
		pthread_join(wtid[i],NULL);
		pthread_join(rtid[i],NULL);
		
	}

}
