/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
Problem 1
*/

#include <stdio.h>
#include <stdlib.h>


void set( int* a, int val){
    *a=val;
}

int main(int argc, char** argv){
    int a = 100;
    int b = 12;
    //print out value of a
    printf("test is %d\n", a);
    //change a
    set(&a,b);
    //print out again
    printf("test is %d\n", a);

}
