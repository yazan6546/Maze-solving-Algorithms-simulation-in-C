#ifndef OK_STACK_H
#define OK_STACK_H

#include <stdlib.h>


// the struct(we can say its like class in java hava atributes and we can make an object from this struct):
typedef struct  Node{
    int data[2];              // <<<  will store the data in the node.
    struct Node* next;    // <<<  will store the address of the next node (points on the NEXT NODE thats why its data is struct node).
    struct Node *top;
}Node;



void push(Node* stack, int x, int y);
int* pop(Node* stack);
int* top(Node* stack);
void deleteStack(Node* stack);
int sizeOf(Node* stack);
int empty(Node* stack);
Node* createStack();
#endif //OK_STACK_H
