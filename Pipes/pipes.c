#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/time.h>
// Communication between processes using pipes 
int main() {
    int fd1[2]; // C => P
    int fd2[2]; // P => C
    
   if( pipe(fd1) == -1){
      printf("An error occured with opening the pipe 1 \n");
      return 1;
   }
   if( pipe(fd2) == -1){
      printf("An error occured with opening the pipe 2 \n");
      return 1;
   }
   int id = fork();
   if(id == 0){
   // Child process
    close(fd2[1]);
    close(fd1[0]);
     int x;
    if(read(fd2[0], &x, sizeof(x)) == -1) {return 2;}
    printf("received %d \n", x);
    x *= 4;
    if(write(fd1[1], &x, sizeof(x)) == -1){return 3;}
    close(fd2[0]);
    close(fd1[1]);
   }else{
   //Parent process
   close(fd1[1]);
   close(fd2[0]);
   //srand(time(NULL));
    int y = rand() % 10;
    if(write(fd2[1], &y, sizeof(y)) == -1){return 4;}
    printf("Generated %d \n",y);
    if(read(fd1[0], &y, sizeof(y)) == -1){return 5;}
    printf("The result is %d \n", y);
    close(fd2[1]);
    close(fd1[0]);
    wait(NULL);
   } 
   
return 0;
}
