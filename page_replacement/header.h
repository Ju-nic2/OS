#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 128
int max;
int size;
int pageFault(int *pageFrame, int num);
void copyToState(int *state, int *origin);
