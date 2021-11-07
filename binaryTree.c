#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* rightChild;
    struct Node* leftChild;
};
struct Node* root;
int elements = 0;
void print(){

}
void insert(int value){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = value;
    struct Node* current;
    struct Node* parent;
    if(root == NULL){
        root = node;
    }
    else{
        current = root;
        parent = NULL;
        while(1){
            parent = current;
            if(value < parent->data){
                current = current->leftChild;

                if(current == NULL){
                    parent->leftChild = node;
                    elements++;
                    return ;
                }
            }
            else{
                current = current->rightChild;
                if(current == NULL){
                    parent->rightChild = node;
                    elements++;
                    return;
                }
            }
        }
    }
}

struct Node* search(int value){
    struct Node* current;
    struct Node* parent;
    if(root == NULL){
        return NULL;
    }
    else{
        current = root;
        parent = NULL;
        while(current->data != value){
            parent = current;
            
            if(value < parent->data){
               
                current = current->leftChild;    
            }
            else{
                current = current->rightChild;
            }
            
            if(current == NULL){
                return NULL;
            }
        }
        return current;
    }
}

int main(void){
  struct Node* find = search(1);
  printf("%d \n",find == NULL);
  insert(7);
  insert(9);
  insert(1);
  find = search(10);
  printf("%d \n",find == NULL);
}
