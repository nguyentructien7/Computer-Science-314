/*-----------------------------------------------------------------//
Author: Tien Nguyen
Date: sept/5/2018
Problem 8
*/

#include <stdio.h>
#include <stdlib.h>

//BST
struct treenode {
    int value;
    struct treenode* left;
    struct treenode* right;
};

struct stack {
    struct treenode* node;
    struct stack* next;
    
};


void push (struct stack* head, struct treenode* input){
    struct stack* current = head;
     struct stack* previous = NULL;
    while( current != NULL){
        previous=current;
        current=current->next;
    }
    
    current = malloc(sizeof(struct stack));
    current->next=NULL;
    current->node=input;
}

void pop(struct stack** head){
    printf("%d\n",head->node->value);
    head=head->next;
}

//insert a child on to the head
struct treenode* insert (struct treenode* head, int val){
    //allocating memory for it
    struct treenode* child = malloc(sizeof(struct treenode));
    struct treenode* current = head;
    struct treenode* previous = NULL;
    
    child->left=NULL;
    child->right=NULL;
    child->value=val;
    
    //finding a spot
    while ( current != NULL){
        previous = current;
        if (val < current->value){
            current = current->left;
            
        }else{
            current = current->right;
        }
    }
    //inserting it
    if (val < previous->value){
        previous->left=child;
        
    }else{
        previous->right=child;
    }
    return child;
}

//print left right
void preorderPrint(struct treenode* head){
    if (head==NULL)
        return;
        
    printf("%d \n", head->value);
    //recursion
    preorderPrint(head->left);
    preorderPrint(head->right);
}

void nr_preorder_print(struct treenode*){
    
}

int main(int argc, char** argv){
    struct treenode* root= malloc(sizeof(struct treenode));
    root->left=NULL;
    root->right=NULL;
    root->value=100;
    
    insert(root,75);
    insert(root,50);
    insert(root,125);
    insert(root,25);
    insert(root,150);
    
    nr_preorder_print(root)
    
    
}
