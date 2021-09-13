#include <stdio.h>

/*
THEORY:
Pointers is a variable that store address of another variable / value
We can use it as a reference to another value, variable in RAM.
*/

//passing by value
int whatIsMore(int a, int b){
    if(a == b){
        return 0;
    }
    if(a > b){
        return 1;
    }
    return -1;
}

//passing by reference
void swap(int* a, int* b){
    int tmp = (*a);
    *a = *b;
    *b = tmp;
}

/*Passing array as a function parameter is simply pass a pointer to the first element of an array*/
int sum(int A[], int size){
    int i = 0;
    int sum = 0;
    while(i < size){
        
        //it is the same as: 
        //sum += (*(A+i));
        sum+= A[i];
        i++;
    }
    return sum;
}

int main(){
    int seventeen = 17;
    int *pnt17 = &seventeen;
    int threeteen = 13;
    int *pnt13 = &threeteen;

    printf("Variable address = %d \n",&seventeen);
    printf("Value of pointer = %d \n",pnt17);
    printf("Value of variable %d \n",*pnt17);

    swap(pnt17,pnt13);
    printf("Value of variable 17 = %d \n", *pnt17);
    printf("Value of variable 13 = %d \n", *pnt13);

    int arr[] = {5,5,5};
    int sumOfArr = sum(arr,(sizeof(arr)/sizeof(int)));
    printf("Sum of elements is %d",sumOfArr);
}