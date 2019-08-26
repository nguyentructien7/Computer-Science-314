/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
homework 2 number 5
*/


#include <stdio.h>
#include <pthread.h>

static pthread_mutex_t sema2 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t sema3 = PTHREAD_MUTEX_INITIALIZER;

int main()  {
    pthread_t thread1, thread2, thread3;
    void *f1();
    pthread_create(&thread1,NULL,f1,1);
    pthread_create(&thread2,NULL,f1,2);
    pthread_create(&thread3,NULL,f1,3);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    pthread_join(thread3, NULL);
    return 0; }
void *f1(int x){
    
    // >0 unlock
    // <=0 lock
    //defualt = 1
    
    if (x==1){
        printf("%d\n", x);
        pthread_mutex_unlock(&sema2);
    }
    else if (x==2){
        //bring it down to 0 if its not already
        pthread_mutex_lock(&sema2);//--
        //actually lock it
        pthread_mutex_lock(&sema2);
        printf("%d\n", x);
        pthread_mutex_unlock(&sema3);
        
    }
    else if (x==3){
        pthread_mutex_lock(&sema3);
        pthread_mutex_lock(&sema3);
        printf("%d\n", x);
        
    }
    
    
    pthread_exit(0);
}
