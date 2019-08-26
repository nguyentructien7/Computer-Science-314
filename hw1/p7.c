/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
Problem 7
*/

#include <stdio.h>
#include <stdlib.h>


struct listnode{
    struct listnode* next;
    int value;
    struct listnode* previous;
    

};

void printlist(struct listnode* head){
    int i=0;
    
    while(head != NULL){
        printf("%d element is %d \n",i, head->value );
        head = head->next;
        i++;
    }
}


void reverse( struct listnode** head){
    struct listnode* temp;
    struct listnode* current= *head;
    while( (current) !=NULL){
        temp = (current)->next;
        (current)->next = (current)->previous;
        (current)->previous = temp;
        (current) = (current)->previous;
    }
    while((*head)->previous != NULL){
    *head=(*head)->previous;
    
    }
}

int main(int argc, char** argv){
    //allocating memory
    //definding a pointer
    struct listnode* root = malloc(sizeof(struct listnode));
    root->value= 10;
    root->next= NULL;
    root->previous= NULL;
    struct listnode* child = malloc(sizeof(struct listnode));
    child->value= 13;
    child->next=NULL;
    child->previous=NULL;
    struct listnode* child2 = malloc(sizeof(struct listnode));
    child2->value= 130;
    child2->next=NULL;
    child2->previous=NULL;
    
    //link the root and the child together
    root->next = child;
    child->previous = root;
    root->next->next=child2;
    child2->previous=child;
    printlist(root);
    reverse(&root);
    printlist(root);
    
    
   
    
    
}
