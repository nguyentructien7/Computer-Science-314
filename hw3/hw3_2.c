/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
homework 2 number 2
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <semaphore.h>

typedef pthread_mutex_t semaphore;
semaphore db = PTHREAD_MUTEX_INITIALIZER;
char* buffer;
int bufferSize = 1;
int bufferIndex = 0;
char* data = "Hello World!";
int dataIndex = 0;

void up(semaphore* mutex){
    pthread_mutex_unlock(mutex);
}

void down(semaphore* mutex){
    pthread_mutex_lock(mutex);
}

void *consumer(void){
    while(dataIndex < strlen(data) && bufferIndex != 0){
        down(&db);
        if(bufferIndex > 0){
            printf("Removing %c from buffer\n", buffer[--bufferIndex]);
        }else{
            printf("Buffer is empty\n");
        }
        up(&db);
    }
}

void *producer(void){
    while(dataIndex < strlen(data)){
        down(&db);
        if(bufferIndex < bufferSize){
            buffer[bufferIndex++] = data[dataIndex++];
            printf("Adding %c to buffer\n", data[dataIndex-1]);
        }else{
            printf("Buffer is full\n");
        }
        up(&db);
    }
}

int main(int argc, char** argv){
    if (argc<4){
        printf("Not enough Command Line Parameters, expected 3.\n");
        return 1;
    }
    
    bufferSize = atoi(argv[3]);
    buffer= malloc(sizeof(char)*bufferSize);
    for(int i = 0; i < bufferSize; i++){
        buffer[i] = '\0';
    }
    
    int producerCnt= atoi(argv[1]);
    int consumerCnt = atoi(argv[2]);
    pthread_t producers[producerCnt];
    pthread_t consumers[consumerCnt];
    
    for( int i = 0; i<producerCnt;i++ ){
         pthread_create(&(producers[i]),NULL,producer,(void*)NULL);
    }
    for( int i = 0; i<consumerCnt;i++ ){
        pthread_create(&(consumers[i]),NULL,consumer,(void*)NULL);
    }
    
    for( int i = 0; i<producerCnt;i++ ){
        pthread_join((producers[i]), NULL);
    }
    for( int i = 0; i<consumerCnt;i++ ){
        pthread_join((consumers[i]), NULL);
    }
}
