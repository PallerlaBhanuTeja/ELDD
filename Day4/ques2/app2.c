#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<stdlib.h>

int main()
{
	int FileDesc;
	char Ubuff[] = "This is User Buffer.. Sending data to Kernel buffer..";
	char Kbuff[100];
	FileDesc = open("/dev/MyCharDevice2",O_RDWR,0777);
	if(FileDesc < 0)
	{
		printf("\n Error Operating Device\n");
		exit(1);
	}
	write(FileDesc, Ubuff, sizeof(Ubuff));
	read(FileDesc,Kbuff, sizeof(Kbuff));
	printf("\n Data read from kernel is \n >> %s << \n ",Kbuff);
	close(FileDesc);
}
