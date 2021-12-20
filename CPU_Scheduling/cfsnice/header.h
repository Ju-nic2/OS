#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MATRIX_SIZE 1024
#define SHM_KEY 1234
struct processInfo
{
	pid_t pid;
	struct timeval start;
	struct timeval end;
	int work;
	int niceValue;
};
void make_matrix(float *matrix);
void initMatrix(float *matrix);
int min(int a, int b);
void matrixMultiple(float *A, float *B,float * result, int repeatNum);
void swap(struct processInfo *A, struct processInfo *B);
void sortByStartTime(struct processInfo *p,int flag);
