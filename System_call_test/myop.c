#include "myheader.h"
long* my_add(long operand1, long operand2)
{
	long* result = (long*)malloc(sizeof(long));
	long err = syscall(443,operand1,operand2,result);
	if(err == -EFAULT) return NULL;
	return result;
}

long* my_sub(long operand1, long operand2)
{
	long* result = (long*)malloc(sizeof(long));
	long err = syscall(444,operand1,operand2,result);
	if(err == -EFAULT) return NULL;
	return result;
}

long* my_mul(long operand1, long operand2)
{
	long *result = (long*) malloc(sizeof(long));
	long err = syscall(445,operand1,operand2,result);
	if(err == -EFAULT) return NULL;
	return result;
}

long* my_mod(long operand1, long operand2)
{
	long *result = (long*)malloc(sizeof(long));
	long err = syscall(446,operand1,operand2,result);
	if(err == -EFAULT) return NULL;
	return result;
}
