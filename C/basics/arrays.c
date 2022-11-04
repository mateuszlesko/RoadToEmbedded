#include <stdio.h>
#include <stdlib.h>


#define max_length 25

unsigned int actual_length = 0;

void insert_between(int* arr,int length,int position, int value){
	int i = 0;
	for(i = length; i >= position-1; i--){
		arr[i+1] = arr[i];
	}
	arr[position-1]= value;
}

void insert_to_array(int* arr, int position, int value){
	if(arr[position-1] == 0 && arr[position] ==0 ){
		arr[position-1] = value;
	}else{
		insert_between(arr,actual_length,position,value);
	}
	actual_length++;
}

int main(void){
	int a [max_length]={0};
	insert_to_array(a,1,2);
	insert_to_array(a,2,9);
	insert_to_array(a,3,5);
	insert_to_array(a,2,4);
	int i;
	for(i = 0; i < actual_length+1;i++){
		printf("%d, ",a[i]);
	}
	Matrix m1 = createMatrix()
}