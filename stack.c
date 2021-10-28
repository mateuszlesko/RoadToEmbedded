#include <stdio.h>
#include <stdlib.h>


struct Node{
    int data;
    struct Node* next;
};


struct StackList{
    struct Node* top;
    int count;
};

int pull(struct StackList** stack){

    if((*stack)->count == 0){
        return -1;
    }
    struct Node* node;
    node = (*stack)->top;
    (*stack)->top = (*stack)->top->next;
    
    (*stack)->count = (*stack)->count-1;
    return node->data;
}

void print(struct StackList** stackPointer){
    struct Node* tmp = (*stackPointer)->top;
    while(tmp != NULL){
        printf("%d, ",tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

void put(struct StackList** stackPointer, int value){
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = value;
    
    struct Node* prevTop = (struct Node*) malloc(sizeof(struct Node));
    prevTop = (*stackPointer)->top;
    node->next = prevTop;
    (*stackPointer)->top = node;
    (*stackPointer)->count = (*stackPointer)->count+1;
}

int main(void){

    struct StackList* stack = (struct StackList*) malloc(sizeof(struct StackList));
    stack->top = (struct Node*) malloc(sizeof(struct Node));
    stack->count = 0;
    struct StackList** stackPointer = (struct StackList**) malloc(sizeof(struct StackList));
    
    stackPointer = &stack;
    
    put(stackPointer,2);
    put(stackPointer,4);

    print(stackPointer);
    pull(stackPointer);
    print(stackPointer);
    printf("elements count: %d",(*stackPointer)->count);
    return 0;
}