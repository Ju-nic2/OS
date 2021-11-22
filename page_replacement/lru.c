#include "header.h"
typedef struct stack{
	int data;
	struct stack *left;
	struct stack *right;
}STACK;

STACK *head = NULL;
STACK *tail = NULL; 

STACK* makeNode(int input)
{
	STACK *node = malloc(sizeof(STACK));
	node->data = input;
	node->left = NULL;
	node->right = NULL;
	return node;
}
int isEmpty()
{
	if(head == NULL) return 1;
	return 0;
}
STACK* search(int num)
{
	STACK* tmp = head;
	tmp = tmp->right;
	while(tmp != NULL)
	{
		if(tmp->data == num)
			return tmp;
		tmp = tmp->right;
	}
	return NULL;	
}
int top()
{
	if(head != NULL)
		return head->data;
	return -1;
}
void push(int input)
{
	if(isEmpty())
	{
		head = makeNode(input);
		tail = head;
	}else if(input != top()) {
		STACK *cur = search(input);
	   	if(cur != NULL){
			cur->left->right = cur->right;
			if(cur != tail)
				cur->right->left = cur->left;
			else
				tail = cur->left;
			head->left = cur;
			cur->right = head;
			cur->left = NULL;
			head = cur;
		}else{
			cur = makeNode(input);
			cur->right = head;
			head->left = cur;
			head = cur;
		}
	}
}
int findMostRecentPage(int *pageFrame)
{
	if(max == 1)
		return 0;
	STACK *cur = tail;
	while(cur != head)
	{
		for(int i = 0; i < max; i++)
		{
			if(cur->data == pageFrame[i])
				return i;
		}
		cur = cur->left;
	}
}

int **lru(int *pageReference, int refCount, int frameNum)
{
	max = frameNum;
	size = 0;
	int *pageFrame = malloc(sizeof(int) * frameNum);
	int **pageFrameState = malloc(sizeof(int*) * refCount);
	for(int i = 0; i < refCount; i++)
	{
		pageFrameState[i] = malloc(sizeof(int) * (frameNum+2));
		memset(pageFrameState[i],-1,(frameNum+2)*sizeof(int));
	}
	for(int i = 0; i < refCount; i++)
	{
		int next = pageReference[i];
		push(next);
		if(pageFault(pageFrame,next))
		{
			if(size < max)
			{
				pageFrame[size++] = next;
			}else{
				int replace = findMostRecentPage(pageFrame);
				pageFrame[replace] = next;
			}
			pageFrameState[i][frameNum+1] = 1;
		}
			copyToState(pageFrameState[i],pageFrame);
	}
	return pageFrameState;
}
