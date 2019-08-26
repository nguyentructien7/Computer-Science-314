/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
Problem 5
*/

#include <stdio.h>
#include <stdlib.h>


struct listnode{
    struct listnode* next;
    int value;

};

void printlist(struct listnode* head){
    int i=0;
    
    while(head != NULL){
        printf("%d element is %d \n",i, head->value );
        head = head->next;
        i++;
    }
}

struct listnode* findNthElement( struct listnode* head, int N){
    //trying to find the N child
    for (int i=0; i<N; i++){
        head = head->next;
    }
    return head;
}

void removeNthElement( struct listnode* head, int N){
    struct listnode* current=head;
    struct listnode* previous;
    
    //trying to find the N child
    for (int i=0; i<N; i++){
        previous=current;
        current= current->next;
    }
    previous->next = current->next;
    free(current);
    
}



int main(int argc, char** argv){
    //allocating memory
    //definding a pointer
    struct listnode* root = malloc(sizeof(struct listnode));
    root->value= 10;
    root->next= NULL;
    struct listnode* child = malloc(sizeof(struct listnode));
    child->value= 13;
    child->next=NULL;
    struct listnode* child2 = malloc(sizeof(struct listnode));
    child2->value= 130;
    child2->next=NULL;
    
    //link the root and the child together
    root->next = child;
    root->next->next=child2;
    printlist(root);
    removeNthElement(root,1);
    printf("print the list again after deletion \n");
    printlist(root);
    
}
