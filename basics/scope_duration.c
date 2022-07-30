#include <stdlib.h>
#include <stdio.h>
//file scope; all have access to this, life long like program execution time
float PI = 3.14159;

//function prototype scope; only function has access to param r
float calculate_full_pole_roller(float r,float H);
void increment(void);

float calculate_full_pole_roller(float r,float H)
{
    //block scope; life long like block exectution time
    //the new PI in block scope is going to be overlaped to PI from file scope
    float PI = 3.14;
    printf("block #1 PI value is:%f \n",PI);
    
    float roller_bases,roller_wall = 0.0;
    {
         //block scope; life long like block exectution time
    //the new PI in block scope is going to be overlaped to PI from outer block scope
        float PI = 3.1;
        printf("block #2 PI value is:%f \n",PI);
        roller_bases = 2*PI*r*r;
    }
    {
        roller_wall = 2*PI*r*H;
    }

   
    return roller_bases+roller_wall;
}

void increment(void){
    /*thanks to `static` keyboard we can tell compiler to assign inital value only once
     - after every execution the previous value will be remember; storage duration will be as long as program is running*/
    static unsigned int i = 0;
    i++;
    printf("%d \n",i);
    return;
}

int main(void){
    printf("global PI value is:%f \n",PI);
    float roll = calculate_full_pole_roller(1.5,1.0);
    printf("Increment #1:",increment());
    printf("Increment #2:",increment());
    return EXIT_SUCCESS;
}