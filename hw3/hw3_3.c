/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
homework 2 number 4
*/

#include <stdio.h>
#include <pthread.h>

pthread_mutex_t * mutex;

//cond a maker for which threat to wake up
pthread_cond_t * condA;
pthread_cond_t * condB;
//semaphore value
int intA = 0;
int intB = 0;
//atomic cant be interupted
void sem_signal(pthread_cond_t *semaSignal, int* i){
    pthread_mutex_lock(mutex);
    *i = *i + 1;
    pthread_cond_signal(semaSignal);//wake up anyone on thread semaSignal
    pthread_mutex_unlock(mutex);//get out atomic section
}
void sem_wait(pthread_cond_t *semaWait, int* i){
    pthread_mutex_lock(mutex);
    *i = *i - 1;
    while (i < 0)
        pthread_cond_wait(semaWait,mutex);
    pthread_mutex_unlock(mutex);
}

void threadA( ){
    printf("a1\n");
    sem_signal(condA, &intA);
    sem_wait(condB, &intB);
    printf("a2\n");
}
void threadB( ){
    printf("b1\n");
    sem_signal(condB, &intB);
    sem_wait(condA, &intA);
    printf("b2\n");
}

int main()  {
    pthread_t A;
    pthread_t B;
    
    //Allocate memory for condition variables
    condA = malloc(sizeof(pthread_cond_t));
    condB = malloc(sizeof(pthread_cond_t));
    //initalize condition variable
    pthread_cond_init(condA,NULL);
    pthread_cond_init(condB,NULL);
    //allocating the memory to the pointer
    mutex = malloc(sizeof(pthread_mutex_t));
    //initialize semaphore
    pthread_mutex_init(mutex, NULL);
    //create the threat
    pthread_create(&A,NULL,threadA,(void*)NULL);
    pthread_create(&B,NULL,threadB,(void*)NULL);
    //waiting for the threat to be done
    pthread_join(A, NULL);
    pthread_join(B, NULL);
}
