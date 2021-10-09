#include "myheader.h"

TOKEN token;
long num;
char ch = ' ';

void print_error(char *str)
{
	fprintf(stderr,"%s\n",str);
	exit(1);
}
void get_token()
{
	while(ch == ' ')
		ch = getchar();
	
	if(ch == '+'){
		token = PLUS;
	}else if(ch == '-')
		token = MINUS;
	else if(ch == '*')
		token = STAR;
	else if(ch == '%')
		token = PERSENT;
	else if(ch >= '0' && ch <= '9')
	{
		token = NUMBER;
		long tmp = 0;
		do{
			tmp = tmp*10 + ch - '0';
			ch = getchar();
		}while(ch >= '0' && ch <= '9');
		num = tmp;
	}
	else if(ch == '(')
	{
		token = NUMBER;
		long tmp = 0;
		ch = getchar();
		if(ch == '-'){
			ch = getchar();
			while(ch >= '0' && ch <= '9'){
				tmp = tmp*10 + ch - '0';
				ch = getchar();
			}
		}
		if(ch != ')')
			print_error("negative num error");
		else
			num = 0 - tmp;
		ch = getchar();	
	}
	else if(ch == '\n')
		token = END;
	else
		print_error("wrong input1");
}

int term()
{
	int result;
	if(token == NUMBER)
	{
		result = num;
		return result;
	}
	print_error("wrong input3");
}

long expression()
{
	long num1,num2;
	long *result;
	num1 = term();

	while(token != END)
	{
		get_token();
		if(token == PLUS)
		{
			ch = getchar();
			get_token(); 
			num2 = term();
			result = my_add(num1,num2);
		}else if(token == MINUS)
		{
			ch = getchar();
			get_token();
			num2 = term();
			result = my_sub(num1,num2);
		}else if(token == STAR)
		{
			ch = getchar();
			get_token();
			num2 = term();
			result = my_mul(num1,num2);
		}else if(token == PERSENT)
		{
			ch = getchar();
			get_token();
			num2 = term();
			result = my_mod(num1,num2);
		}else if(token == END)
		{
			break;
		}
		else
			print_error("wrong operation2");
	}
	if(result == NULL)
		print_error("kernel_error");

	return *result;	
}


int main()
{
	get_token();
	long result = expression();
	printf("= %d\n",result);
}
