/*
List is a data structure where we store a given number of elements of any time
Reading elements is by their position on the list. Also we can modify elements at position
The list is collection of data that have the same type.

Concrete implementation of the list is array. 
*/
#include<stdio.h>
#include<stdlib.h>

static int End = -1;
int* createIntegerList(int size){
    int* arr = (int*) calloc(size,sizeof(int));
    return arr;
}
int* resizeIntegerList(int* array, int size){
    free(array);
    int* newArray = (int*) realloc(array,size);
    return newArray;
}
void storeDataAt(int* arr,int index, int value){
    arr[index] = value;
}

int size(){
    return End;
}

void storeData(int* arr, int value){
    if(End >= 0){
        *(arr+End) = value;
        End = End+1;
    }
    else{
        End = 0;
        *(arr+End) = value;
    }
}

void printList(int* arr,int size){
    int i;
    for(i = 0; i < size; i++){
        printf("%d, ",*(arr+i));
    }
    printf("\n");
}
//method finding specific value in list and then return value's index; if list doesn't contain value return -1
int findElement(int* arr, int value, int size){
    int i = 0;
    for(i = 0; i < size; i++){
        if(value == arr[i]){
            return i;
        }
    }
    return -1;
}
void removeElementAt(int* arr,int index,int size){
    int i;
    for(i = index+1; i < size; i++){
        arr[i-1] = arr[i]; 
    }
    End = End-1;
}

int main(void){
    int* intArray = createIntegerList(10);
    storeData(intArray,0);
    storeData(intArray,1);
    storeData(intArray,2);
    storeData(intArray,3);
    storeData(intArray,4);
    printf("%d \n",intArray[0]);
    storeDataAt(intArray,0,1);
    printList(intArray,End);
    removeElementAt(intArray,1,End);
    printList(intArray,End);
}