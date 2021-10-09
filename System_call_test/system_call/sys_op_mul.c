#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>

asmlinkage long sys_op_mul(long operand1, long operand2,long* des)
{
	long result = operand1 * operand2;
	if(copy_to_user(des,&result,sizeof(result)))
		return -EFAULT;
	return 0;	
}

SYSCALL_DEFINE3(op_mul, long, operand1, long, operand2, long*, des)
{
	return sys_op_mul(operand1,operand2,des);
}
