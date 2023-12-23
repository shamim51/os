#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <semaphore.h>

sem_t x, y, z , rsem, wsem;
int readcount, writecount;

void initialize() {
	sem_init(&rsem, 0, 1);
	sem_init(&wsem, 0, 1);
	sem_init(&x, 0, 1);
	sem_init(&y, 0, 1);
	sem_init(&z, 0, 1);
	readcount = 0;
	writecount = 0;
}

void* reader(void* arg) {
	sem_wait(&z);
	sem_wait(&rsem);
	sem_wait(&x);
	printf("Reader is trying to enter\n");
	sleep(1);
	readcount++;
	if (readcount == 1) {
		sem_wait(&wsem);
	}
	sem_post(&x);
	sem_post(&rsem);
	sem_post(&z);
	printf("%d no Reader is inside \n", readcount);
	sleep(1);
	printf("Reader is leaving\n");
	sem_wait(&x);
	readcount--;
	if (readcount == 0) {
		sem_post(&wsem);
	}
	sem_post(&x);
}
void* writer(void* arg) {
	printf("Writer is trying to enter\n");
	sleep(1);
	sem_wait(&y);
	writecount++;
	if (writecount == 1) {
		sem_wait(&rsem);
	}
	sem_post(&y);
	sem_wait(&wsem);
	printf("%d no writer has entered the critical section\n", writecount);
	sleep(1);
	printf("writer is leaving\n");
	sem_post(&wsem);
	sem_wait(&y);
	writecount--;
	if (writecount == 0) {
		sem_post(&rsem);
	}
	sem_post(&y);
}

int main()
{
	int r = 5;
	int w = 3;
	pthread_t rtid[r];
	pthread_t wtid[w];
	initialize();
	for (int i = 0; i < r; ++i)
	{
		pthread_create(&(rtid[i]), NULL, &reader, NULL);
	}
	for (int i = 0; i < w; ++i)
	{
		pthread_create(&(wtid[i]), NULL, &writer, NULL);
	}


	for (int i = 0; i < r; ++i)
	{
		pthread_join(rtid[i], NULL);
	}

	for (int i = 0; i < w; ++i)
	{
		pthread_join(wtid[i], NULL);
	}
	return 0;
}

/*
gcc -o D D.c -lpthread
./D
*/
