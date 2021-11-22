#include "header.h"

int** fifo(int *pageReference, int refCount, int frameNum)
{
	int resent = -1;
	max = frameNum;
	size = 0;
	int *pageFrame = malloc(sizeof(int) * frameNum);
	memset(pageFrame,-1,(frameNum) * sizeof(int));
	int **pageFrameState = malloc(sizeof(int*) * refCount);
	for(int i = 0; i < refCount; i++)
	{
		pageFrameState[i] = malloc(sizeof(int) * (frameNum+2));
		memset(pageFrameState[i],-1,(frameNum+2)*sizeof(int));
	}
	for(int i = 0; i < refCount; i++)
	{
		int next = pageReference[i];
		if(pageFault(pageFrame,next))
		{

			if(size < max){
				size++;}
			if(resent == size-1){
				resent = -1;}
			pageFrame[++resent] = next;
			pageFrameState[i][frameNum+1] = 1;
		}

		copyToState(pageFrameState[i],pageFrame);
	}
	return pageFrameState;
}
