#include <stdio.h>
#include <fcntl.h>

int main()
{
    int fd1, fd2, fd3, fd4, num1, num2;
    printf("Enter two numbers: \n");
    scanf("%d", &num1);
    scanf("%d", &num2);
    char Ubuf1[20] = "";
    char Ubuf2[20] = "";
    char Kbuf[100];
    sprintf(Ubuf1, "%d", num1);
    sprintf(Ubuf2, "%d", num2);
    fd1 = open("/dev/DeviceA", O_RDWR, 0777);
    if(fd1 < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
 
    fd2 = open("/dev/DeviceS", O_RDWR, 0777);
    if(fd2 < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    fd3 = open("/dev/DeviceM", O_RDWR, 0777);
    if(fd3 < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    fd4 = open("/dev/DeviceD", O_RDWR, 0777);
    if(fd4 < 0)
    {
        printf("Error opening Device.\n");
        exit(1);
    }
    
    write(fd1, Ubuf1, 20);
    write(fd1, Ubuf2, 20);
    read(fd1, Kbuf, 80);
    printf("Data read from kernel i.e addition of %d and %d : \n%s\n", num1, num2, Kbuf);

    write(fd2, Ubuf1, sizeof(int));
    write(fd2, Ubuf2, sizeof(int));
    read(fd2, Kbuf, 80);
    printf("Data read from kernel i.e subtraction of %d from %d : \n%s\n", num2, num1, Kbuf);

    write(fd3, Ubuf1, sizeof(int));
    write(fd3, Ubuf2, sizeof(int));
    read(fd3, Kbuf, 80);
    printf("Data read from kernel i.e multiplication of %d and %d : \n%s\n", num1, num2, Kbuf);

    write(fd4, Ubuf1, sizeof(int));
    write(fd4, Ubuf2, sizeof(int));
    read(fd4, Kbuf, 80);
    printf("Data read from kernel i.e division of %d from %d : \n%s\n", num1, num2, Kbuf);
    
    close(fd1);
    close(fd2);
    close(fd3);
    close(fd4);  
    
    return 0;
}
