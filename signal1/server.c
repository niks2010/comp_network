#include  <stdio.h>
#include  <sys/types.h>
#include  <signal.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <unistd.h>
#include  <stdlib.h>
#include  <fcntl.h>
#include  <malloc.h>

void  SIGINT_handler(int);   
void  SIGQUIT_handler(int); 

int   ShmID;      
pid_t *ShmPTR;    

void main(void)
{
     int   i;
     pid_t pid = getpid();
     key_t MyKey;

     if (signal(SIGINT, SIGINT_handler) == SIG_ERR) {  //Use SIGUSR1 or SIGUSR2
          printf("SIGINT install error\n");
          exit(1);
     }
     if (signal(SIGQUIT, SIGQUIT_handler) == SIG_ERR) {
          printf("SIGQUIT install error\n");
          exit(2);
     }

	//raise if you want to call inside raise(SIGINT);

     MyKey   = ftok(".", 's');    
     ShmID   = shmget(MyKey, sizeof(pid_t), IPC_CREAT | 0666);
     ShmPTR  = (pid_t *) shmat(ShmID, NULL, 0);
     *ShmPTR = pid;               

     for (i = 0; ; i++) {   
     	  char *myfifo = "/home/niks/my_codes/comp_network/signal1/myfifo";
	  mkfifo(myfifo,0777);
	  int fd = open(myfifo,O_RDONLY);
	  char *msg = (char*) malloc(sizeof(char)*1024);
	  read(fd,msg,1024);
	  printf("msg got: %s\n",msg);     
          printf("From process %d: %d\n", pid, i);
          sleep(1);
          close(fd);
     }
}

void  SIGINT_handler(int sig)
{
     signal(sig, SIG_IGN);
     printf("From SIGINT: just got a %d (SIGINT ^C) signal\n", sig);
     signal(sig, SIGINT_handler);
}

void  SIGQUIT_handler(int sig)
{
     signal(sig, SIG_IGN);
     printf("From SIGQUIT: just got a %d (SIGQUIT ^\\) signal"
                          " and is about to quit\n", sig);
     shmdt(ShmPTR);
     shmctl(ShmID, IPC_RMID, NULL);

     exit(3);
}

