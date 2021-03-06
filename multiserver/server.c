#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <error.h>
#include <fcntl.h>
#include <malloc.h>
#include <string.h>

#define MAX_SIZE 1024

char* msg;

void fifo_input(){
	char *myfifo = "/home/niks/my_codes/comp_network/multiserver/myfifo";
	int fd;
	char* tmp = (char*) malloc(sizeof(char)*MAX_SIZE);
	fd = open(myfifo,O_RDONLY);
	read(fd,tmp,MAX_SIZE);
	strcpy(msg,tmp);
	printf("%s",msg);
}


void pipe_input(){
	int fd[2];
	int pid;
	
	pid = fork();
	pipe(fd);
	
	if(pid == 0){	//child process
		close(fd[0]);
		char* tmp = (char*) malloc(sizeof(char)*MAX_SIZE);
		printf("Enter your msg.\n");
		scanf("%s",tmp);
		write(fd[1],tmp,MAX_SIZE);
	}
	
	else{
		wait(1);
		char* tmp = (char*) malloc(sizeof(char)*MAX_SIZE);
		close(fd[1]);
		read(fd[0],tmp,MAX_SIZE);
		printf("message got: %s\n",tmp);
		strcat(msg,tmp);
	}
	
	printf("%s",msg);
}


int main(){
	msg = (char*) malloc(sizeof(char)*MAX_SIZE);
	fifo_input();
	pipe_input();
}
