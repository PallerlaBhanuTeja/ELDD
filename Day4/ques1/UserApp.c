#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>

int main()
{
	int FileDesc;
	char Ubuff[] = "This is User Buffer.. Sending data to Kernel buffer..";
	char Kbuff[100];
	FileDesc = open("/dev/MyCharDevice",O_RDWR,0777);
	if(FileDesc < 0)
	{
		printf("\n Error Operating Device\n");
		exit(1);
	}
	close(FileDesc);
}

