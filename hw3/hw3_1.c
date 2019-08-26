/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
homework 2 number 1
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>

int N = 5;
#define LEFT (i+N-1)%N
#define RIGHT (i+1)%N
#define THINKING 0
#define HUNGRY 1
#define EATING 2
typedef pthread_mutex_t semaphore;
int* state;
semaphore mutex = PTHREAD_MUTEX_INITIALIZER;
semaphore* s;

void *philosopher(int i);
void take_fork(int i);
void put_fork(int i);
void test(int i);
void think(int i);
void eat(int i);
void down(semaphore *sema);
void up(semaphore *sema);
    
void *philosopher(int i){
    for(int j=0; j<10;j++){
      //  think(i);
        take_fork(i);
	//  eat(i);
        put_fork(i);
    }
}

void take_fork(int i){
    down(&mutex);
    state[i]=HUNGRY;
    printf("philosopher %d is hungry\n", i);
    test(i);
    up(&mutex);
    down(&s[i]);
 }

void put_fork(int i){
    down(&mutex);
    state[i]=THINKING;
    printf("philosopher %d is thinking\n", i);
    test(LEFT);
    test(RIGHT);
    up(&mutex);
}

void test(int i){
    if (state[i]==HUNGRY&&state[LEFT]!=EATING && state[RIGHT]!=EATING){
        state[i]= EATING;
        printf("philosopher %d is eating\n", i);
        up(&s[i]);
    }
}

void think(int i){
    printf("philosopher %d is thinking\n", i);
}

void eat(int i){
    printf("philosopher %d is eating\n", i);
    
}

void down(semaphore* sema){
     pthread_mutex_lock(sema);
}

void up(semaphore* sema){
    pthread_mutex_unlock(sema);
}

int main(int argc, char** argv){
    if (argc > 1)
        N = atoi(argv[1]);
    
    state = malloc(sizeof(int)*N);
    s = malloc(sizeof(semaphore)*N);
    pthread_t thread[N];
    for( int i=0; i<N;i++){
        pthread_mutex_init(&(s[i]), NULL);
        
    }
    
    for( int i=0; i<N; i++){
        pthread_create(&(thread[i]),NULL,philosopher,(void*)i);
    }
    
    for( int i=0; i<N; i++){
        pthread_join(thread[i], NULL);
    }
}
