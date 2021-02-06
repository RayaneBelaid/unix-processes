#include <stdio.h>
#include <unistd.h>

int main ()
{
  pid_t child_pid;
  printf("\nID du processus principal: %d \n", (int) getpid());
  child_pid = fork();
  printf("Child id: %d \n", child_pid);
  if(child_pid != 0)
  {
    printf("\nJe suis le processus parent \n");
    printf("\nL'id du processus fils est: %d \n", (int) child_pid);
  }  
  else 
  {
    printf("\nJe suis le processus fils, ID = %d \n",(int) getpid());
  }
return 0;

}
