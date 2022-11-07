#include <stdio.h>
#include <stdlib.h>

/* data types are divided into:
- object
- function

***OBJECT***
the object type means that somewhere in memory is allocated space for store value 
the definition of object was presented in ISO/IEC 9899-2018
***FUNCTION***
these aren't objects, but they have types. Fuction type is characterised by return type and types of its params
*/
int main(void){
    printf("size of short: %lu bytes \n",sizeof(short));
    printf("size of int: %lu bytes \n",sizeof(int));
    printf("size of char: %lu bytes \n",sizeof(char));
    printf("size of float: %lu bytes \n", sizeof(float));
    printf("size of double: %lu bytes \n",sizeof(double));
    printf("size of timestamp: %lu bytes \n",sizeof(__TIMESTAMP__));

    return EXIT_SUCCESS;
}