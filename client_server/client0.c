#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <string.h>
#include <fcntl.h>

#define MAX_SIZE 1024

int main(){
	char myfifo[MAX_SIZE] = "/home/niks/my_codes/comp_network/client_server/myfifo0";
	int fd;
	
	printf("fd %d\n",fd);
	
	while(1){
		fd = open(myfifo,O_WRONLY);
	
		char msg[MAX_SIZE];
		printf("Write your message.\n");
		scanf("%s",msg);
		write(fd,msg,MAX_SIZE);
		//printf("Received msg is : %s\n",msg);
		if(strcmp(msg,"exit") == 0){
			close(fd);
			break;
		}
		close(fd);
	}
	
	
	return 0;
}
