#include "header.h"

int findOptimalFrame(int *pageFrame,int *pageReference, int start,int end)
{
	int optimal = -1;
	int maxDistance = 0;
	for(int i = 0; i < max; i++)
	{
		int distance = end+1;
		for(int j = start+1; j < end; j++)
		{
			if(pageReference[j] == pageFrame[i]){
				distance = j;
				break;
			}
		}
		if(distance > maxDistance)
		{
			maxDistance = distance;
			optimal = i;
		}
	}
	return optimal;

}
int** optimal(int *pageReference, int refCount, int frameNum)
{
	max = frameNum;
	size = 0;
	int *pageFrame = malloc(sizeof(int) * frameNum);
	int **pageFrameState = malloc(sizeof(int*) * refCount);
	for(int i = 0; i < refCount; i++)
	{
		pageFrameState[i] = malloc(sizeof(int*)*(frameNum+2));
		memset(pageFrameState[i],-1,(frameNum+2)*sizeof(int));
	}

	for(int i = 0 ; i < refCount; i++)
	{
		int next = pageReference[i];
		if(pageFault(pageFrame,next))
		{
			if(size < frameNum)
			{
				pageFrame[size++] = next;	
			}else{
				int replace = findOptimalFrame(pageFrame,pageReference,i,refCount);
				pageFrame[replace] = next;
			}
				pageFrameState[i][frameNum+1] = 1;
		}
		copyToState(pageFrameState[i],pageFrame);
	}
	return pageFrameState;
}

