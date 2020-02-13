#include <unistd.h>
#include <stdio.h>
#include<sys/wait.h>

int main(int argc, char const *argv[]) {

  int the_pipe_ofChild[2];
  int  pipeVal = pipe(the_pipe_ofChild);
  if (pipeVal == -1 ) {
    printf("Pipe failed\n");
  }

  int forkVal =  fork();

  if (forkVal > 0) {
    wait(NULL);
    printf("In parent \n");
    close(the_pipe_ofChild[1]);
    char recieved;
    read(the_pipe_ofChild[0],recieved,10);
    printf("Val of recieved %c \n",&recieved );
  }
  else if(forkVal == 0)
  {
    printf("In Child\n");
    char input;
    scanf("%c",&input );
    close(the_pipe_ofChild[0]);
    write(the_pipe_ofChild[1],(char) input,10);
  }
  return 0;
}
