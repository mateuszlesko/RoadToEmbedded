#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
};

struct QueueList{
    struct Node* first;
    struct Node* last;
    int count;
};

void add(struct QueueList* queuePointer, int value){
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = value;

    if(queuePointer->count == 0){
        queuePointer->first = node;
    }
    else if(queuePointer->count == 1){
        
        queuePointer->last = node;
        queuePointer->first->next  = queuePointer->last;
    }
    else{
        struct Node* prev = (struct Node*) malloc(sizeof(struct Node));
        prev = queuePointer->last;
        queuePointer->last = node;
        prev->next = queuePointer->last;
    }

    queuePointer->count = queuePointer->count+1;
}

int get(struct QueueList* queuePointer){
    int data = queuePointer->first->data;
    struct Node* tmp = queuePointer->first;
    queuePointer->first = queuePointer->first->next;
    queuePointer->count = queuePointer->count - 1;
    free(tmp);
    return data;
}

void print(struct QueueList* queuePointer){
    struct Node* tmp = queuePointer->first;
    while(tmp != NULL){
        printf("%d, ",tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

int main(void){
    struct QueueList* queue = (struct QueueList*) malloc(sizeof(struct QueueList));
    queue->first = (struct Node*) malloc(sizeof(struct Node));
    queue->last = (struct Node*) malloc(sizeof(struct Node));
    queue->count = 0;
    struct QueueList** queuePointer = (struct QueueList**)malloc(sizeof(struct QueueList));
    
   
    add(queue,4);
    add(queue,2);
    int a = get(queue);
    print(queue);
    return 0;
}