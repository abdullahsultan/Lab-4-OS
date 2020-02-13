#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include<sys/wait.h>

int isPalindrome(char str[]);

int main(int argc, char const *argv[]) {

  int the_pipe_1[2];
  int the_pipe_2[2];

  char recieved[20];
  char input[100];
  char pal[100];
  int palchid;

  int  pipeVal = pipe(the_pipe_1);
  if (pipeVal < 0 ) {
    printf("Pipe 1 failed\n");
  }
  if (pipe(the_pipe_2) == -1 ) {
    printf("Pipe 2 failed\n");
  }

  int forkVal =  fork();

  if (forkVal > 0) {
    printf("In parent \n");
    close(the_pipe_1[0]);
    printf("Enter the value\n");
    gets(input);
    writte(the_pipe_1[1], (char*) input,20);

    wait(NULL);
    close(the_pipe_2[1]);
    read(the_pipe_2[0],pal,2);
    if(pal == 1)
    {
      printf("Not plaindrome\n");
    }
    else
      printf("Plaindrome\n");

  }


  else if(forkVal == 0)
  {
    printf("In Child\n");
    close(the_pipe_1[1]);

    read(the_pipe_1[0],recieved,20);
    printf("DUCKKKKKK\n");

    printf("Val of recieved %s \n",&recieved );

    palchid = isPalindrome(recieved);
    close(the_pipe_2[0]);
    write(the_pipe_2[1],palchid,2);


  }
  return 0;
}

int isPalindrome(char str[])
{
    int l = 0;
    int h = strlen(str) - 1;

    while (h > l)
    {
        if (str[l++] != str[h--])
        {
            return 0;
        }
    }
    return 1;
}
