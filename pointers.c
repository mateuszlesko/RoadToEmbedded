#include <stdio.h>
#include <string.h>
#include <ctype.h>
/*
THEORY:
Pointers is a variable that store address of another variable / value
We can use it as a reference to another value, variable in RAM.
*/

//passing by the value
int whatIsMore(int a, int b){
    if(a == b){
        return 0;
    }
    if(a > b){
        return 1;
    }
    return -1;
}

//passing by the reference
void swap(int* a, int* b){
    int tmp = (*a);
    *a = *b;
    *b = tmp;
}

/*Passing array as a function parameter is simply pass a pointer to the first element of an array*/
/*but it doesn't mean that arrays and pointers are the same types*/
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

void string2Upper(char* A){
    while(*A != '\0'){
        *A = toupper((*A));
        A++;
    }
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

    /*
    HOW MANY BYTES FOR DATA TYPES:
    int = 4 bytes
    float = 4 bytes
    char = 1 bytes
    */

    /*We can cast one pointer to another type*/
    int bigInt = 601;
    int* d = &bigInt;
    char* pnt2Char = (char*)d;
    //Char is stored as 1byte and int as 4bytes so if we cast int to char, then the orginal value is changing
    printf("Casted value of int pointer to char = %d \n", *pnt2Char); 
    int arr[] = {1,5,8};
    printf("Address of begining of array = %d \n", *arr);
    //so the next element is at position = first + 4 bytes 
    printf("Address of the next element = %d \n",*(arr+1));
    int sumOfArr = sum(arr,(sizeof(arr)/sizeof(int)));
    printf("Sum of elements is %d \n",sumOfArr);

    char name[]= "Mateusz";
    printf("My name is %s; the count of letters is %d \n",name, strlen(name));
    string2Upper(name);
    printf("My name is %s \n",name);
}