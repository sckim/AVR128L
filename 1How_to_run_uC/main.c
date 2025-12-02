/*
 * 1How_to_run_uC.c
 *
 * Created: 2020-05-01 오전 10:18:01
 * Author : Soochan Kim
 */ 

//#include <avr/io.h>

int add(int a, int b)
{
	return a+b;
}

int main(void)
{
	char *str = "123456";
	
	*str = *str+1;
	
	return 1;
}

