#include <stdlib.h>
#include<stdio.h>

/* union is used where it is not necessarily store all data at the same time*/
typedef union{
    char * name;
    int age;
    int height;
    int weight;
} uperson;

typedef struct{
    char * name;
    int age;
    int height;
    int weight;
} sperson;

void HelloSP(sperson* psp);
void HelloUP(uperson* pup);

void HelloSP(sperson* psp){
    printf("Hello my name is %s. I am %d years old \n",psp->name,psp->age);
}

void HelloUP(uperson* pup){
    printf("Hello I am %d years old \n",pup->age);
}

int main(void){
    uperson p1;
    p1.name = "Wika";
    p1.age = 20;
    p1.height = 170;
    p1.weight = 84;

    sperson p2;
    p2.name = "Wika";
    p2.age = 20;
    p2.height = 170;
    p2.weight = 84;
    
    //the difrence between union and struct is in allocated memory size
    printf("union size:%lu \n",sizeof(uperson));
    printf("struct size:%lu \n",sizeof(sperson));
    
    //So for limited allocated space by union will override data
    printf("union person age %d, height: %d, weight: %d \n",p1.age,p1.height,p1.weight);
    printf("struct person age %d, height: %d, weight: %d \n",p2.age,p2.height,p2.weight);
    
    //for both we can call them by reference
    HelloSP(&p2);
    HelloUP(&p1);
    
    return EXIT_SUCCESS;
}