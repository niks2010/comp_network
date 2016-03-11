#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <error.h>
#include <sys/times.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_SIZE 1024

int main(){
	int fd0,fd1,fd2;
	while(1){
		fd0 = open("myfifo0",O_WRONLY);
		fd1 = open("myfifo1",O_WRONLY);
		fd2 = open("myfifo2",O_WRONLY);
	
		char msg[1024];
		
		printf("Enter your msg\n");
		scanf("%s",msg);
		
		write(fd0,msg,1024);
		/*scanf("%d %d",&data1,&data2);
		write(fd0,data1,1024);
		write(fd0,data2,1024);*/
		write(fd1,msg,1024);
		write(fd2,msg,1024);
	
		close(fd0);
		close(fd1);
		close(fd2);
	}
}
