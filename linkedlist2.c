#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
};

//void AddElement(int value);
//void AddElementAt(int position, int value);
//void removeElementAt(int position);
void printList();

struct Node* head;
int elementsCounter = 0;


void AddElement(struct Node** headPointer, int value){
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = value;

    //making new node a new head
    node->next = (*headPointer);
    node->prev = NULL;

    //changing previous element before head to that
    if((*headPointer) != NULL){
        (*headPointer)->prev = node;
    }

    //move to head;
    (*headPointer) = node;
    elementsCounter++;
}

void AddElementAt(struct Node** headPointer, int position, int value){

    if(position > elementsCounter){
        return;
    }

    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->data = value;

    //when we adding at the begining
    if(position == 0){
        AddElement(headPointer,value);
        return;
    }

    struct Node* positionNode = (struct Node*) malloc(sizeof(struct Node));
    positionNode = (*headPointer);
    int i = 0;
    while(i < position){
        positionNode = positionNode->next;
        i++;
    }

    //when we adding at the end
    if(elementsCounter == position){
        positionNode->next = node;
    }
    //other cases
    else{
        struct Node* previousNode = positionNode->prev; 
        //the next new node is the next of previous
        node->next = previousNode->next;
        //next node of previous node is the newest
        previousNode->next = node;
        node->prev = previousNode;
    }
    elementsCounter++;
}

void removeElement(struct Node** headPointer){
    struct Node* oldHead = (struct Node*) malloc(sizeof(struct Node));
    oldHead = (*headPointer);
    (*headPointer) = (*headPointer)->next;
    printf("NOWY HEADER %d \n", (*headPointer)->data);
    free(oldHead);
    elementsCounter--;
}

// void removeElementAt(struct Node** headPointer, int position){
//     if(position > elementsCounter){
//         return;
//     }

//     if (position == 0){
//         removeElement(headPointer);
//         return;
//     }
    
//     struct Node* positionNode = (struct Node*) malloc(sizeof(struct Node));
//     positionNode = (*headPointer);
//     int i = 0;

//     while(i < position){
//         positionNode = positionNode->next;
//         i++;
//     }
//     if(position > 0 && position < elementsCounter){
//         struct Node* previousNode = (struct Node*) malloc(sizeof(struct Node));
//         struct Node* afterNode = (struct Node*) malloc(sizeof(struct Node));

//         printf("value: %d \n",positionNode->data);
//         previousNode = positionNode->prev;
//         afterNode = positionNode->next;

//         printf("head: %d %d \n",(*headPointer)->next->data,&(*headPointer)->next);
//         printf(": %d  %d \n",positionNode->data, &positionNode);
//         printf("- %d \n",previousNode->data);
//         printf("+ %d \n",afterNode->data);
//         //free(positionNode);

//         elementsCounter--;
//     }     
// }

void printList(){
    struct Node* tmp = head;
    while(tmp != NULL){
        printf("%d ,",tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

int main(void){
    head = (struct Node*) calloc(1,sizeof(struct Node));

    struct Node** headPointer = &head;
    //printf("%d",head->data);
    AddElement(headPointer,1);
    AddElement(headPointer,2);
    AddElement(headPointer,3);
    AddElement(headPointer,4);
    AddElementAt(headPointer,4,8);
    AddElementAt(headPointer,0,9);
    AddElementAt(headPointer,1,10);
    printList();
    printList();
    removeElement(headPointer);
    printList();
    removeElementAt(headPointer,1);
    printList();
    return 0;
}