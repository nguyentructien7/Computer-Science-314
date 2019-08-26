/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
Problem 2
*/

#include <stdio.h>
#include <stdlib.h>

//change the variable it pointing at
// a point to val, val point to a
void swapInts( int* a, int* val){
    int temp = *a;
    *a = *val;
    *val = temp;
    
}

int main(int argc, char** argv){
    int a = 100;
    int b = 12;
    //print out value of a
    printf("var 1 is %d\n", a);
    printf("var 2 is %d\n", b);
    //change a
    swapInts(&a,&b);
    //print out again
    printf("var 1 is %d\n", a);
    printf("var 2 is %d\n", b);
}
