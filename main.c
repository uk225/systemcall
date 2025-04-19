#include<stdio.h>
#include<stdlib.h>
#include "copy.h"


int main(int argc, char *argv[])
{
	int status;
	if(argc!=3)
	{
		printf("invalid arguments,please mention source and destination file path\n");
		return -1;
	}
	status=copy_using_function(argv[1],argv[2]);
	if (status==0)
	{
		printf("result:success\n");
		return 0;
	}
	printf("result:failed\n");
	return -1;
}
