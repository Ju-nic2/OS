#include "header.h"

int** fifo(int *pageReference, int refCount, int frameNum);
int** optimal(int *pageReference, int refCount, int frameNum);
int** lru(int *pageReference, int refCount, int frameNum);
int** second_chance(int *pageReference, int refCount, int frameNum);

int *readInputFile(int *frameNum,int *refCount,char *fileName);
void printStates(int **pageFrameState,int refCount, int frameNum);
void printPageReference(int *pageReference, int refCount);

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr,"please write input file\n");
		exit(1);
	}
	char input[BUFSIZE];
	int frameNum = 0; 
	int refCount = 0;
	int *pageReference = readInputFile(&frameNum,&refCount,argv[1]);
	printf("Used Methon : ");
	scanf("%s",input);
	if( !strcmp(input,"all"))
	{
		printf("Used Methon : OPT\n");
		printPageReference(pageReference,refCount);
		printStates(optimal(pageReference,refCount,frameNum),refCount,frameNum); 
		printf("Used Methon : FIFO\n");
		printPageReference(pageReference,refCount);
		printStates(fifo(pageReference,refCount,frameNum),refCount,frameNum); 
		printf("Used Methon : LRU\n");
		printPageReference(pageReference,refCount);
		printStates(lru(pageReference,refCount,frameNum),refCount,frameNum); 
		printf("Used Methon : Second-Chance\n");
		printPageReference(pageReference,refCount);
		printStates(second_chance(pageReference,refCount,frameNum),refCount,frameNum);
	}	


	if(!strcmp(input,"FIFO") || !strcmp(input,"fifo"))
	{
		printPageReference(pageReference,refCount);
		printStates(fifo(pageReference,refCount,frameNum),refCount,frameNum); 
	}
	if(!strcmp(input,"OPT") || !strcmp(input,"opt"))
	{
		printPageReference(pageReference,refCount);
		printStates(optimal(pageReference,refCount,frameNum),refCount,frameNum); 
	}
	if(!strcmp(input,"LRU") || !strcmp(input,"lru"))
	{
		printPageReference(pageReference,refCount);
		printStates(lru(pageReference,refCount,frameNum),refCount,frameNum); 
	}
	if(!strcmp(input,"Second-Chance") || !strcmp(input,"second-chance"))
	{
		printPageReference(pageReference,refCount);
		printStates(second_chance(pageReference,refCount,frameNum),refCount,frameNum); 
	}

}
void printPageReference(int *pageReference, int refCount){
	printf("page reference string  : ");
	for(int i = 0; i < refCount; i++)
	{
		printf("%d ",pageReference[i]);
	}
	printf("\n");
}

void printStates(int **pageFrameState,int refCount, int frameNum)
{
	int pageFaultCount = 0;
	printf("\tframe");
	for(int i = 0; i < frameNum; i++)
	{
		printf("\t%d",i+1);
	}
	printf("\tpage fault\ntime\n");
	for(int i = 0; i < refCount; i++)
	{
		printf("%d\t\t",i+1);
		for(int j = 1; j <= frameNum; j++)
		{
			if(pageFrameState[i][j] != -1)
				printf("%d\t",pageFrameState[i][j]);
			else
				printf("\t");
		}
		if(pageFrameState[i][frameNum+1] == 1)
		{
			printf("%c\n",'F');
			pageFaultCount++;
		}else{
			printf("%c\n",' ');
		}
	}
		printf("Number Of page faults : %d times\n",pageFaultCount);
}

int * readInputFile(int *frameNum,int *refCount, char *fileName)
{
	FILE *fp;
	if((fp = fopen(fileName,"r")) == NULL)
	{
		fprintf(stderr,"reed input File Error\n");
		exit(1);
	}

	char buffer[BUFSIZE];
	//read page frame num
	memset(buffer,0,BUFSIZE);
	fgets(buffer,BUFSIZE,fp);

	int index = 0;
	while(buffer[index] != '\n')
	{
		*frameNum = (*frameNum)*10 + (buffer[index++] - '0');
	}
	if(*frameNum > 4)
	{
		fprintf(stderr,"Frame Num's Maximum is 4\n");
		exit(1);
	}
	
	//read page reference string 
	memset(buffer,0,BUFSIZE);
	fgets(buffer,BUFSIZE,fp);

	index = 0;
	int referCount = 0;
	while(buffer[index] != '\n' && buffer[index] != EOF)
	{
		if(buffer[index++] == ' ')
			referCount++; 
	}

	if(referCount > 30)
	{
		fprintf(stderr,"ReferCount's Maximum is 30\n");
		exit(1);
	}


	int *pageReference = malloc(sizeof(int) * (referCount+1));
	index = 0;
	referCount = 0;
	while(buffer[index] != '\n' && buffer[index] != EOF)
	{
		if(buffer[index] != ' '){
			pageReference[referCount] = pageReference[referCount] * 10 + (buffer[index++] - '0');
		}
		else{
			referCount++;
			index++;
		}
	}
	*refCount = referCount+1;
	return pageReference;
}
int pageFault(int *pageFrame, int num) 
{
	
	for(int i = 0; i < size; i++)
	{
		if(pageFrame[i] == num)
			return 0;
	}
	return 1;

}

void copyToState(int *state, int *origin)
{
	state[0] = size;
	for(int i = 1; i <= size; i++)
	{
		state[i] = origin[i-1];
	}
}
