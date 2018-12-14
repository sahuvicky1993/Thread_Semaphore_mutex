#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <sched.h>
#define INVALID_DATA 0xffffffff

static void* scanNo(void*arg);
static void* printNo(void*arg);

int scanned_no = INVALID_DATA;
sem_t block;

/* Write a programme to create 2 thread one would read data from user
 * Another one would print the data, by default data value would be '-1'
 * Print fn should not print data until scanned_no becomes valid (non -1)
 */

main(){
	pthread_t pid[2] = {'\0'};
	// init block with 0 sothat print wount execute before scan
	sem_init(&block,0 ,0);
	
	pthread_create(&pid[0],0 ,&scanNo ,0);
	pthread_create(&pid[1],0 ,&printNo ,0);
	
	pthread_join(pid[0],0);
	pthread_join(pid[1],0);
}

void* scanNo(void*arg){
	printf("%s\n", __func__);
	
	if(INVALID_DATA == scanned_no){
		scanf("%d", &scanned_no);
		// let printNo know that we got the data
		sem_post(&block);
	}
}

void* printNo(void*arg){
	printf("%s\n", __func__);
	
	// wait for the signal from scanNo fn
	sem_wait(&block);
	if(INVALID_DATA != scanned_no ){	
		printf("In printNo...""%d \n",scanned_no);
		scanned_no =0;
	}
	else{
		/* this is for debug, try scanning '-1' or init 'block' with 1  */
		printf("We should not be here. Problem with semaph\n");
	}
}
