/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
Problem 4
*/

#include <stdio.h>
#include <stdlib.h>


struct listnode{
    struct listnode* next;
    int value;

};



struct listnode* findNthElement( struct listnode* head, int N){
    //trying to find the N child
    for (int i=0; i<N; i++){
        head = head->next;
    }
    return head;
}


int main(int argc, char** argv){
    //allocating memory
    //definding a pointer
    struct listnode* root = malloc(sizeof(struct listnode));
    root->value= 10;
    struct listnode* child = malloc(sizeof(struct listnode));
    child->value= 13;
    
    //link the root and the child together
    root->next = child;
    //print
    printf("root has a value of %d\n", root->value);
    printf("child has a value of %d\n", child->value);
    printf("root first child has a value of %d\n", findNthElement(root,1)->value);
    
}
