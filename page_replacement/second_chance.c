#include "header.h"
int findNextVictim(int *referenceBit, int cur)
{
	if(max == 1) return 0;
	if(cur == max) cur = 0;

	while(referenceBit[cur] != 0){
		if(referenceBit[cur] == 1) 
			referenceBit[cur] = 0;
		cur++;
		if(cur == max) cur = 0;
	}

	return cur;	
}

void setReferenceBit(int *pageFrame, int *referenceBit, int num)
{
	for(int j = 0; j < max; j++)
	{
		if(pageFrame[j] == num)
		{
			referenceBit[j] = 1;
			break;
		}	
	}			
}
int** second_chance(int *pageReference, int refCount, int frameNum)
{
	max = frameNum;
	size = 0;
	int *pageFrame = malloc(sizeof(int) * frameNum);
	int *referenceBit = malloc(sizeof(int) * frameNum);
	int **pageFrameState = malloc(sizeof(int*) * refCount);
	for(int i = 0; i < refCount; i++)
	{
		pageFrameState[i] = malloc(sizeof(int*)*(frameNum+2));
		memset(pageFrameState[i],-1,(frameNum+2)*sizeof(int));
	}
	int victim = 0;
	for(int i = 0 ; i < refCount; i++)
	{
		int next = pageReference[i];
		if(pageFault(pageFrame,next))
		{
			if(size < max)
			{
				pageFrame[size++] = next;
			}else{
				victim = findNextVictim(referenceBit,victim);
				pageFrame[victim++] = next;
			}
			pageFrameState[i][frameNum+1] = 1;
		}
		else{
			setReferenceBit(pageFrame,referenceBit,next);
		}
		copyToState(pageFrameState[i],pageFrame);
	}
	return pageFrameState;
}

