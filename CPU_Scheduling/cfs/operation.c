#include "header.h"

void make_matrix(float *matrix)
{
	srand((unsigned int)time(NULL));
	for(int i = 0; i < MATRIX_SIZE; i++)
	{
		for(int j = 0; j < MATRIX_SIZE; j++)
		{
			matrix[i*MATRIX_SIZE + j] = rand()%10;
		}
	}
}
void initMatrix(float *matrix)
{
	for(int i = 0; i < MATRIX_SIZE; i++){
		for(int j = 0; j < MATRIX_SIZE; j++){
			matrix[i*MATRIX_SIZE + j] = 0;
		}
	}
}
int min(int a, int b)
{
	return (a < b) ? a : b;
}
void swap(struct processInfo *A, struct processInfo *B)
{
	struct processInfo tmp = *A;
	*A = *B;
	*B = tmp;
}

void sortByTime(struct processInfo *p,int flag)
{
	if(flag == 1){
		for(int i = 0; i < 21; i++)
		{
			for(int j = 0; j < 20 - i; j++)
			{
				if(p[j].start.tv_sec > p[j+1].start.tv_sec)
				{
					swap(&p[j],&p[j+1]);
				}else if(p[j].start.tv_usec > p[j+1].start.tv_usec)
				{
					swap(&p[j],&p[j+1]);
				}
			}
		}
	}else{
		for(int i = 0; i < 21; i++)
		{
			for(int j = 0; j < 20 - i; j++)
			{
				if(p[j].end.tv_sec > p[j+1].end.tv_sec)
				{
					swap(&p[j],&p[j+1]);
				}else if(p[j].end.tv_usec > p[j+1].end.tv_usec)
				{
					swap(&p[j],&p[j+1]);
				}
			}
		}
	}
		
}
void matrixMultiple(float *A, float *B,float * result, int repeatNum)
{
	int count = 0;
	while(count < repeatNum){
	for(int i = 0; i < MATRIX_SIZE; i++){
		for(int j = 0; j < MATRIX_SIZE; j++){
			result[i*MATRIX_SIZE + j] = A[i*MATRIX_SIZE + j] + B[i*MATRIX_SIZE + j];
		}
	}
	count++;
	}
}


