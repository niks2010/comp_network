//client 1
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <poll.h>
#include <fcntl.h>
#include <error.h>

#define MAX_SIZE 1024

int main(){
	int fd,i;
	char myfifo[MAX_SIZE] = "/home/niks/my_codes/comp_network/poll/myfifo1";
	char msg[MAX_SIZE];
	
	while(1){
		printf("Enter your msg (Type \"exit\" to exit) : ");
		scanf("%s",msg);
		fd = open(myfifo,O_WRONLY);
		write(fd,msg,MAX_SIZE);
		close(fd);
		if(strcmp(msg,"exit") == 0){
			break;
		}
	}
	
	return 0;
}
