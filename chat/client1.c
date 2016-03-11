#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <sys/poll.h>

#define MAX_SIZE 1024

int* pid;
int* int_buf;
int fd;
int shmid_pid,shmid_flg;

void shm_create(){
	key_t key = 123;
	shmid_pid = shmget(key,MAX_SIZE,IPC_CREAT | 0777);
	pid = (int*) shmat(shmid_pid,NULL,0);
	
	key = 456;
	shmid_flg = shmget(key,MAX_SIZE,IPC_CREAT | 0777);
	int_buf = (int*) shmat(shmid_flg,NULL,0);
}

int main(){
	shm_create();
	char* myfifo = "/home/niks/my_codes/comp_network/chat/myfifo1";
	char* msg = (char*) malloc(sizeof(char)*MAX_SIZE);
	fd = open(myfifo,O_RDWR);
	while(1){
		if((*pid != 1)&& (*int_buf & POLLIN)){
			read(fd,msg,MAX_SIZE);
			printf("Message sent from client %d is : %s",*pid,msg);
		}
	
		if(*pid == 1 && (*int_buf )){//& POLLOUT)){
			printf("Enter your msg .\n");
			scanf("%s",msg);
			
			write(fd,msg,MAX_SIZE);
		}
	}
	
	return 0;
}
