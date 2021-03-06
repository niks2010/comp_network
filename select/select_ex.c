#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <error.h>
#include <sys/times.h>
#include <sys/types.h>
#include <fcntl.h>

#define MAX_SIZE 1024

int nfds = 3;
fd_set readfds,writefds,exceptfds;
struct timeval timeout;

int main(){
	mkfifo("myfifo0",0777);
	mkfifo("myfifo1",0777);
	mkfifo("myfifo2",0777);
	
	int fd0 = open("myfifo0",O_RDONLY);
	int fd1 = open("myfifo1",O_RDONLY);
	int fd2 = open("myfifo2",O_RDONLY);
	char msg[1024];
	//printf("%d\n",fd0);
	
	//int fd0,fd1,fd2;
	
	//read(fd0,msg,1024);
	//printf("msg : %s\n",msg);
	
	FD_ZERO(&readfds);	//clear
	FD_SET(fd0,&readfds);	//fd0 is added to readfds
	FD_SET(fd1,&readfds);	//fd1 is added to readfds
	FD_SET(fd2,&readfds);
	
	printf("%d\n",FD_ISSET(fd0,&readfds));
		
	timeout.tv_sec = 5;	//seconds
	timeout.tv_usec = 0;	//microseconds
	


	while(1){
		int retval = select(4,&readfds,NULL,NULL,&timeout); //select(FD_SETSIZE,&readfds,&writefds,&exceptionfds,&timeout)

		if(retval == -1)
			perror("select()\n");
		else if(retval){
			read(fd0,msg,1024);
			if(strcmp(msg,"exit\0") == 0)
				exit(0);
			printf("Data is available now :%s\n",msg);
			read(fd1,msg,1024);
			printf("Data is available now :%s\n",msg);
			read(fd2,msg,1024);
			printf("Data is available now :%s\n",msg);
		}
		else
			printf("No data within five seconds.\n");
		
		sleep(5);
	}
	unlink("myfifo0");
	unlink("myfifo1");
	unlink("myfifo2");
			return 0;
}
