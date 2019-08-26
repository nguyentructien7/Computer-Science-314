/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
homework 2 number 4
*/

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t sema = PTHREAD_MUTEX_INITIALIZER;


#define MAX 100000
FILE* out;
int main()  {
    pthread_t f3_thread, f2_thread, f1_thread;
    void *f1();
    int i = 0;
    pthread_mutex_init(&sema, NULL);
    out = fopen("numbers", "w+");

    pthread_create(&f1_thread,NULL,f1,(void*)&i);
    pthread_create(&f2_thread,NULL,f1,(void*)&i);
    pthread_create(&f3_thread,NULL,f1,(void*)&i);
    pthread_join(f1_thread, NULL);
    pthread_join(f2_thread, NULL);
    pthread_join(f3_thread, NULL);
    fclose(out);
    return 0;
}
void *f1(int * x){
    
    while(*x < MAX){
        pthread_mutex_lock(&sema);
        if (*x < MAX){
            fprintf(out,"%d\n", *x);
            (*x)++;
        }
        pthread_mutex_unlock(&sema);
    }
    
    pthread_exit(0);
}
 
