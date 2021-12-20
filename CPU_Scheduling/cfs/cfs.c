#include "header.h"


struct processInfo* procs;
int initSharedMemory()
{
	int shm_id;
	if((shm_id = shmget(SHM_KEY, sizeof(struct processInfo)*21,IPC_CREAT|0644)) == -1)
	{
		fprintf(stderr,"make shared memory error\n");
		return -1;
	}

	if((procs = (struct processInfo*)shmat(shm_id,NULL,0)) == NULL)
	{
		fprintf(stderr,"get shared memory error\n");
		return -1;
	}
	return shm_id;
}

int freeSharedMemeory(int shm_id)
{
	if(shmctl(shm_id,IPC_RMID,0) == -1)
	{
		fprintf(stderr,"free shared memory error\n");
		return -1;
	}
	return 0;
}


int main()
{
	int shm_id;
	
	//allocate shared memory for saving result
	shm_id = initSharedMemory();

	pid_t pid;
	for(int i = 0; i < 21; i++)
	{
		//child process
		pid = fork();
		if(pid == 0)
		{
			int err,repeatNum = 100;
			gettimeofday(&procs[i].start,NULL);
			procs[i].pid = getpid();
			procs[i].work = repeatNum*(21);
			printf("Start process %d work : %d \n",procs[i].pid,procs[i].work);
			
			float *matrix1 = malloc(sizeof(float)*(MATRIX_SIZE*MATRIX_SIZE));
			float *matrix2 = malloc(sizeof(float)*(MATRIX_SIZE*MATRIX_SIZE));
			float *result = malloc(sizeof(float)*(MATRIX_SIZE*MATRIX_SIZE));
			
			make_matrix(matrix1);
			make_matrix(matrix2);
			initMatrix(result);
			
			matrixMultiple(matrix1,matrix2,result,repeatNum*(21));
			
			gettimeofday(&procs[i].end,NULL);
			printf("END process %d work : %d \n",procs[i].pid,procs[i].work);
			free(matrix1);
			free(matrix2);
			free(result);
			i = 22;
			
			
			exit(1);
		}
	}

	for(int i = 0; i < 21; i++)
	{
		waitpid(procs[i].pid,NULL,0);
	}
	printf("start sort\n");
	sortByTime(procs,1);
	for(int i = 0; i < 21; i++)
	{
		printf("process %d work : %d ",procs[i].pid,procs[i].work);
		struct tm *lts;
		lts = localtime(&procs[i].start.tv_sec);
		printf("start at %02d:%02d.%06ld ",lts->tm_min,lts->tm_sec,procs[i].start.tv_usec);
		struct tm *lte;
		lte = localtime(&procs[i].end.tv_sec);
		printf("end at %02d:%02d.%06ld ",lte->tm_min,lte->tm_sec,procs[i].end.tv_usec);
		

		
		printf("total time : %.fms\n",	(double)((procs[i].end.tv_sec - procs[i].start.tv_sec)* 1000 + 
									(procs[i].end.tv_usec - procs[i].start.tv_usec)/1000));
		
	}
	printf("end sort\n");
	sortByTime(procs,0);
	for(int i = 0; i < 21; i++)
	{
		printf("process %d work : %d ",procs[i].pid,procs[i].work);
		struct tm *lte;
		lte = localtime(&procs[i].end.tv_sec);
		printf("end at %02d:%02d.%06ld ",lte->tm_min,lte->tm_sec,procs[i].end.tv_usec);
		struct tm *lts;
		lts = localtime(&procs[i].start.tv_sec);
		printf("start at %02d:%02d.%06ld ",lts->tm_min,lts->tm_sec,procs[i].start.tv_usec);

		
		printf("total time : %.fms\n",	(double)((procs[i].end.tv_sec - procs[i].start.tv_sec)* 1000 + 
									(procs[i].end.tv_usec - procs[i].start.tv_usec)/1000));
		
	}
	

	freeSharedMemeory(shm_id);
	printf("end\n");

}
