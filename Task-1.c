#include <unistd.h>
#include <stdio.h>
#include<sys/wait.h>
#include<string.h>
int main(int argc, char const *argv[]) {

  int the_pipe[2];
  int  pipeVal = pipe(the_pipe);
  if (pipeVal == -1 ) {
    printf("Pipe failed\n");
  }

  int forkVal =  fork();

  if (forkVal > 0) {
    //wait(NULL);
    printf("In parent \n");
    close(the_pipe[1]);
    char recieved[100];
    int rcvd = read(the_pipe[0],(char*)recieved,10);
    printf("%d, Val of recieved %s \n",rcvd, recieved );
  }
  else if(forkVal == 0)
  {
    printf("In Child\n");
    char input[10];
    scanf("%s",input);
    //strcpy(input,"test");
    printf("%s\n",input);
    close(the_pipe[0]);
    int sent=write(the_pipe[1],(char*)input,10);
    printf("Bytes sent %d\n",sent);
  }
  return 0;
}
