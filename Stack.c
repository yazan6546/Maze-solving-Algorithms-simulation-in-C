#include "Stack.h"
#include <stdio.h>
/* Stacks: is a list  with the restreaction that insertion and deletion can be performed only at one postion
(the end of list -> called TOP)

The fundamental operations of the stack are:
• Push: equivalent to insert. Inserts element at top.
• Pop: return and delete the most recently added element .
• Top: examines (returns) the most recently added element without deleteing it.

*NOTE: pop or top on empty stack is generally considered an error*

we can implement the stack using:
• Linked list.
• Dynamic array.

 _______________________________
| Top    |      |      |       |
|        |      |      |       |
|   >    |   >  |   >  |       |


*/

//______________________________________________________   👇🏽 by linked list 👇🏽  ______________________________________________________ //

// to make a shortcut of data we can USE 'typedef' KeyWord:
// typedef struct Node* List   >>>  now List = struct node*
// typedef List Postion >>>>  now  Postion = List = struct node*




Node* createStack() {
    Node *stack = malloc(sizeof(struct Node));
    stack->next = NULL;

    return stack;
}

//Push function: equivalent to insert. Inserts element at top:
void push(Node* stack, int x, int y) {

    Node* newNode = (Node*)malloc(sizeof(Node)); //<-- to find a address in the memo to save the new node in it.

    // if there is no space in the memo for this node tell the user:
    if (newNode == NULL) {
        return;
    }

    newNode->data[0] = x;//<-- sets the data of the newNode to be the element.
    newNode->data[1] = y;
    printf("%d\n", newNode->data[0]);
    newNode->next = stack->next;    //<-- sets the next pointer of newNode to point to the current top of the stack).
    stack->next = newNode;       //<-- sets the newNode to be the top(stack) node(top of the stack),  making it the new top of the stack.

}


//Pop function: return AND delete the most recently added element:
int* pop(Node* stack) {

    // if the theere is no elements inside the stack there is nothing to pop so it will cuse an error:
    if (stack->next == NULL) {
        return NULL;
    }

    Node* temp = stack->next;              //<--  temporary node will pointer to top node.
    int *poppedElement = malloc(2 * sizeof(int));
    poppedElement[0] = temp->data[0]; //<-- to store the data that was in the last top.
    poppedElement[1] = temp->data[1];
    stack->next = temp->next;            //<-- will make the next node of the pervious top to be the the final top.
    free(temp);                   //<-- free the temp (node) from the memo.
    return poppedElement;   //<-- return the poppedElement.

}

//getTop: examines (returns) the most recently added element without deleteing it:
int* top(Node* stack) {

    // if the theere is no elements inside the stack there is nothing to pop so it will cuse an error:
    if (stack->next == NULL) {
        return NULL;
    }
    return stack->next->data;  //<-- will return the elemnt that in the top node.
}

//deleteStack function : will delete the nedeed stack:
void deleteStack(Node* stack) {

    // will delete all the nodes:
    while (stack->next!=NULL) {
        Node* temp = stack->next;
        stack = stack->next;
        free(temp->data);
        free(temp);
    }

    free(stack);
}

//sizeOf: to get the size of the stack:
int sizeOf(Node* stack) {

    int size = 0;
    while (stack->next != NULL) {
        stack = stack->next;
        size++;
    }
    return size;
}


//isEmpty: return if the stack is null or not:
int empty(Node* stack){
    return (stack->next == NULL); //<-- to return if the stack is null or not
}


