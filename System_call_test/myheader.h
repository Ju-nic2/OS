#include <stdio.h>
#include <unistd.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <stdlib.h>
#include <errno.h>
typedef enum {PLUS,MINUS,STAR,PERSENT,NUMBER,END}TOKEN;

long* my_add(long operand1,long operand2);
long* my_mul(long operand1,long operand2);
long* my_mod(long operand1,long operand2);
long* my_sub(long operand1,long operand2);
