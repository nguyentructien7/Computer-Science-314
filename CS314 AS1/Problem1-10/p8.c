/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
Problem 8
*/

#include <stdio.h>
#include <stdlib.h>


struct listnode{
    struct listnode* next;
    char value;
    struct listnode* previous;
    

};

void printlist(struct listnode* head){
    int i=0;
    
    while(head != NULL){
        printf("%d element is %c \n",i, head->value );
        head = head->next;
        i++;
    }
}

void printRev(struct listnode* head){
    int i=0;
    
    while(head != NULL){
        printf("%d element is %c \n",i, head->value );
        head = head->previous;
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

int isPalyndrome (struct listnode* head){
    struct listnode* temp=head;
    struct listnode* previous;
    struct listnode* current;
    
    //creating a new list
    while( temp != NULL){
        previous = current;
        current = malloc(sizeof(struct listnode));
        current->next= NULL;
        current->previous=NULL;
        current->value = temp->value;
        current->previous = previous;
        temp = temp->next;
        if (previous !=NULL)
        previous->next=current;
        
    }
    reverse(&current);
    temp=head;
    
    while (temp != NULL){
        if( temp->value != current->value){
            return (0);
        
        }
        temp = temp->next;
        current = current->next;
    }
    
    return (1);
    
}



int main(int argc, char** argv){
    //allocating memory
    //definding a pointer
    struct listnode* root = malloc(sizeof(struct listnode));
    root->value= 'a';
    root->next= NULL;
    root->previous= NULL;
    struct listnode* child = malloc(sizeof(struct listnode));
    child->value= 'b';
    child->next=NULL;
    child->previous=NULL;
    struct listnode* child2 = malloc(sizeof(struct listnode));
    child2->value= 'a';
    child2->next=NULL;
    child2->previous=NULL;
    
    //link the root and the child together
    root->next = child;
    child->previous = root;
    root->next->next=child2;
    child2->previous=child;
    printlist(root);
    if (isPalyndrome(root)==1){
        printf("The list is a Palyndrome\n");
    }else{
        printf("The list is not a Palyndrome\n");
    }
    
}
