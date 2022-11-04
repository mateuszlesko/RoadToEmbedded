#include <stdio.h>
#include <stdlib.h>

typedef struct Matrix{
	int **data;
	unsigned int rows;
	unsigned int cols;

}Matrix;


void print_matrix(int** arr,unsigned int rows,unsigned int cols){
	int r,c;
	for(r = 0; r < rows; r++){
		for(c = 0; c < cols;c++){
			printf(" %d ",arr[r][c]);
		}
		printf("\n");
	}
}

Matrix* create_matrix(unsigned int rows,unsigned int cols){
	
	int** matrix1 = (int**)malloc(rows*sizeof(int*));
	for(int i = 0; i < rows; i++){
		matrix1[i] = (int*)malloc(cols*sizeof(int*));
	}

	unsigned int r;
	unsigned int c;
	int element = 0;
	int value = 0;
	for(r = 0; r < rows; r++){
		for(c = 0; c < cols;c++){
			printf("Press %d matrix element: \n",element);
			scanf("%d",&value);
			matrix1[r][c] = value;
			printf("%d",matrix1[r][c]);
			element++;
			printf("\n");
		}
	}
	printf("Given matrix: \n");
	print_matrix(matrix1,rows,cols);
	// for(r = 0; r < rows; r++){
	// 	for(c = 0; c < cols;c++){
	// 		printf(" %d ",matrix1[r][c]);
	// 	}
	// 	printf("\n");
	// }

	Matrix* matrix = (Matrix*)malloc(sizeof(Matrix*));
	matrix->data = matrix1;
	matrix->rows = rows;
	matrix->cols = cols;
	return matrix;
}

int get_matrix_dimensions(char* what,unsigned char nr){
	int data = 0;
	while(data < 1){
		printf("%s in  %d matrix \n",what, nr);
		scanf("%d",&data);
		if(data <= 0){
			printf("%s must be more than 0",what);
		}
	}
	return data;
}

void clean_memory(Matrix* m){
	for (int i = 0; i < m->rows;i++){
		free(m->data[i]);
	}
	free(m);
}


unsigned char multiple_matrixes(Matrix* m1, Matrix* m2, Matrix* result){
	if(m1->rows != m2->cols){
		return 1;
	} 

	result->rows = *&(m1->rows);
	result->cols = *&(m2->cols);

	result->data = (int**)malloc(result->rows*sizeof(int*));

	for(int i  = 0; i < result->rows; i++){
		result->data[i] = (int*)malloc(result->cols*sizeof(int*));
		printf("%d,",i);
	}
	for(int i  = 0; i < m1->rows;i++){
		for(int j = 0; j < m1->cols;j++){
			for(int k = 0; k < m2->rows;k++){
				result->data[i][j]=result->data[i][j]+m1->data[i][k]*m2->data[k][j];
			}
		}
	}
	return 0;
}

int main(void){
	unsigned int rows1 = 0;
	unsigned int rows2 = 0;
	unsigned int cols1 = 0;
	unsigned int cols2 = 0;

	rows1 = get_matrix_dimensions("rows",1);
	cols1 = get_matrix_dimensions("cols",1);

	Matrix* m1 = create_matrix(rows1,cols1);

	rows2 = get_matrix_dimensions("rows",2);
	cols2 = get_matrix_dimensions("cols",2);

	Matrix* m2 = create_matrix(rows2,cols2);
	Matrix* multiply_res = (Matrix*)malloc(sizeof(Matrix*));
	unsigned char res = multiple_matrixes(m1,m2,multiply_res);
	if(res == 1){
	printf("not able to multiply");
		free(multiply_res);
	}else{
		printf("operation result:\n");
		print_matrix(multiply_res->data,multiply_res->rows,multiply_res->cols);
	}

	clean_memory(m1);
	clean_memory(m2);
	free(multiply_res);
	//clean_memory(multiply_res);
}