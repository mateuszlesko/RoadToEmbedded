/*
*****NOTES*****
memmove vs memcopy
memmove seems to be more safely approach to move memory from one place to another, memmove is general option, and always successed.
memcopy is vulnerable of memory overlap. There are some cases where memcopy won't work. 
memcpy implementation has less code than memmove so it might be faster using memcpy. Memmove has additional instructions to check if memory overlap. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_SIZE 6

char remove_element(int* arr, int len, int toRemove){
    if (toRemove < 0 || toRemove >= len){
        return 0;
    }
    //removing by shifting values to specified position
    memmove(arr+1,arr,sizeof(int)*toRemove);
    arr[0]=0;
    return 1;
}

int main(void){

    int arr[ARRAY_SIZE] = {1,2,3,4,5,6};

    for(int i =0; i < ARRAY_SIZE;i++){
        printf("%d ,",arr[i]);
    }
    printf("\n");
    remove_element(arr,ARRAY_SIZE,3);
     for(int i =0; i < ARRAY_SIZE;i++){
        printf("%d ,",arr[i]);
    }

    return EXIT_SUCCESS;
}