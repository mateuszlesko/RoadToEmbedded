#include <stdio.h>
#include <string.h>
#include<stdlib.h>
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

//because stack after end function deallocated memory; the pointer to value can be erased
//passing value from bottom to top won't make problems but getting data from stack top level in bottom level can.
//the right approach is to save data in heap
int* multiply(int* a, int* b){
    //WRONG:
    //int c = (*a) * (*b);
    //RIGHT:
    int* c = (int*) malloc(sizeof(int));
    *c = (*a) * (*b);
    return c;
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
    /*Multidimensional arrays*/
    //int - every address of an array next element is up about 2 bytes
    //multidimensional array in memory is next to each other
    //mean: 1000: 1, 1002: 2, 1004: 3, 1006:4
    int arr2d[2][2] = { {1,2},{3,4}};
    int* pnt2d = &arr2d[0][0];
    printf("%d \n",*(pnt2d+2));
    printf("%d \n",*(arr2d[0]+1));

    /*dynamic heap memory allocation*/
    /*override pointer to some value in heap does not clear it; it is still in computer memory. We need manauly delete it */
    int x1; //stack stores x1
    
    /*
    functions that allocate block of heap memory:
    - malloc; void* malloc(size_t size); size_t is a positive int (how many bytes needs to be allocated); function do not set value; not initialize
    - calloc; void* calloc(size_t num, size_t size); num =  number of elements, size = size of data type; function set all bytes with 0; initialize 
    - realloc; void* realloc(void* pointer, size_t size); pointer = reference to pointer, size = size of data type function change block memory size;
    copy all data
    
    function that deallocate block of heap memory:
    - free
    */

    //WRONG:
    void* PP = malloc(sizeof(int));
    //*PP = 23; //CAN NOT dereference void pointer; need cast;
    printf("%d %d \n",PP);
    //RIGHT:
    int* pHeap;
    pHeap = (int*)malloc(sizeof(int)); //if there is no room for data then function return null
    *pHeap = 10;
    free(pHeap);
    //if we want store array in heap: we simply multiply size of data type by array size
    char* pArray = (char*)malloc(4*sizeof(char));
    *pArray = 'M';
    pArray[1] = 'A';
    *(pArray+2) = 'T';
    pArray[3]  = 'I';
    printf("%s \n",pArray);

    free(pArray);
    pArray = (char*)calloc(5,sizeof(char));
    //or : pArray = (char*)realloc(pArray,sizeof(char));
    pArray[0] = 'L';
    pArray[1] = 'E';
    pArray[2] = 'S';
    pArray[3] = 'K';
    pArray[4] = 'O'; 
    printf("%s \n",pArray);

    int n;
    int* A;
    printf("Enter size of array: \n");
    scanf("%d",&n);
    if(n <= 0 ){
        printf("Wrong number");
    }
    else{
        A = (int*) calloc(n,sizeof(int));
    }
    free(A);
    int* result = multiply(pnt17,pnt13);
    printf("%d \n",*result);
    free(result);

}