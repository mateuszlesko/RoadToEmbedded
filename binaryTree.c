#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node* rightChild;
    struct Node* leftChild;
};
struct Node* root;
int elements = 0;

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

void swap(struct Node* a, struct Node* b){
    struct Node* tmp = a;
    a->data = b->data;
    b->data = tmp->data;
}

struct Node* searchMinValueInRightSide(){
    if(root != NULL){
        struct Node* tmp = (struct Node*) malloc(sizeof(struct Node));
        tmp = root;
        while(tmp->rightChild->rightChild != NULL){
            tmp = tmp->rightChild;
        }
        return  tmp->leftChild != NULL ? tmp->leftChild : NULL;
    }
    return NULL;

}

void removeFromTree(int value){
    struct Node* node2Delete = search(value);

    //the last elements
    if(node2Delete->leftChild == NULL && node2Delete->rightChild == NULL)
        free(node2Delete);
    //have one child
    else if(node2Delete->leftChild != NULL && node2Delete->rightChild == NULL){
        swap(node2Delete,node2Delete->leftChild);
        free(node2Delete->leftChild);
    }
    //have one child
    else if(node2Delete->leftChild == NULL && node2Delete->rightChild != NULL){
        swap(node2Delete,node2Delete->rightChild);
        free(node2Delete->rightChild);
    }
    //have both child
    else{
        struct Node* tmp = searchMinValueInRightSide();
        swap(root,tmp);
        free(tmp);
    }
}

int main(void){
  struct Node* find = search(1);
  printf("%d \n",find == NULL);
  insert(50);
  insert(40);
  insert(70);
  insert(60);
  insert(80);
  find = search(80);
  printf("80 before deletion %d \n",find == NULL);
  removeFromTree(80);
  find = search(80);
  printf("80 after deletion %d \n",find == NULL);
  printf("root before deletion %d \n",root->data);
  //remove root
  removeFromTree(50);
  printf("root before deletion %d \n",root->data); 
}
