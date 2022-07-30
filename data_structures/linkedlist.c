#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};


void addElement(int data);
void addElementAt(int position, int data);
void printList();

struct Node* head = NULL;
int listSize = 0;


void printList(){
    struct Node* tmp = head;
    printf("LINKED LIST:");
    while(tmp != NULL){
        printf("%d, ",tmp->data);
        tmp = tmp->next;
    }
    printf("\n");
}

void addElement(int data)
{
    struct Node* temp = (struct Node*)malloc(sizeof(struct Node));
    temp->data = data;
    temp->next = head;
    head = temp;
    listSize = listSize+1;
}

void addElementAt(int position, int value){
    if(position > listSize){
        return;
    }
    struct Node* tmp = (struct Node*) malloc(sizeof(struct Node));
    tmp->data = value;
    tmp->next = NULL;
    //if we want add something at begining
    if(position == 1){
        tmp->next = head;
        head = tmp;
        listSize = listSize+1;
        return;
    }
    int i = 0;
    struct Node* iterator = head;
    //we iterate for element after list
    while(i < position-2){
        iterator = iterator->next;
    }
    //put node in the right place
    tmp->next = iterator->next;
    iterator->next = tmp;
    listSize = listSize+1;
}

void removeElement(){
    struct Node* tmp = head;
    head = tmp->next;
    free(tmp);
    listSize = listSize-1;
}
void removeElementAt(int position){
    
    if(position > listSize){
        return;
    }
    
    if(position == 1){
        struct Node* tmp = head;
        head = tmp->next;
        free(tmp);
        return;
    }

    struct Node* tmp = head;
    int i = 0;
    while(i < position - 2){
        tmp = tmp->next;
        i++;
    }
    //the node that we want to delete
    struct Node* tmp2 = tmp->next;
    //connect node before the right one to the node after it
    tmp->next = tmp2->next;
    listSize--;
    free(tmp2);
}

int size(){
    return listSize;
}

int main(void){
    addElement(11);
    addElement(12);
    addElementAt(2,8);
    removeElement();
    addElement(12);
    addElement(14);
    removeElementAt(3);
    printList();
    return 0;
}