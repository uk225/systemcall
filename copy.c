#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>

int copy_using_syscall(char *source,char *destination)
{
	char buffer[4096];
	int fd1,fd2,_stat,count;

	struct stat sb;

        _stat=stat(source,&sb);

        if (_stat!=0)
        {
		perror("unable to fetch metadata");
		return -1;
        }
	printf("blocksize is %ld\n",sb.st_blksize);

	fd1 = open(source,O_RDONLY,0);
	if (fd1< 0)
	{
		perror("error opening the file");
		return -1;
	}

	fd2=open(destination,O_WRONLY |O_CREAT| O_TRUNC,0666);
	if(fd2<0)
	{
		perror("error in opening the file");
		return -1;
	}


	do
	{
		count = read(fd1,buffer,sb.st_blksize);
		write(fd2,buffer,count);

	}
	while(count == sb.st_blksize);

	close(fd1);
	close(fd2);
	
	
	return 0;
}


int copy_using_function(char *source,char *destination)
{
	int fp1,count;
	FILE *fp2=NULL;
	int _stat;
	char buffer[4096];


	struct stat sb;
	_stat = stat(source,&sb);
	if (_stat !=0)
	{
		perror("unable to fetch metadata");
                return -1;
	}

	fp1 = open(source,O_RDONLY,0);
        if (fp1< 0)
        {
                perror("error opening the file");
                return -1;
        }
	fp2 = fopen(destination,"w+");
	if(fp2==NULL)
	{
		perror("error in opening the file");
		return -1;
	}
	do
        {
                count = read(fp1,buffer,sb.st_blksize);
                fwrite(buffer,1,count,fp2);
		//write(fd2,buffer,count);
        }
        while(count == sb.st_blksize);

	close(fp1);
	fclose(fp2);
}
