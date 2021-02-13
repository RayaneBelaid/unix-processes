#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

//2 processes calculate the sum of an array using pipe() function

int main ()
{
int arr[]={1,2,3,4,1,2,5,6};
int arrSize = sizeof(arr) / sizeof(int); // nbr of byte / size of int
int start, end;
int fd[2];
if(pipe(fd) == -1){
  printf("An error occured on the opening \n");
  return 1;
}
int id = fork();
if (id == -1){
   return 2;
}
if(id == 0){
//child 
start = 0;
end = arrSize / 2;

}else {
//parent
start = arrSize / 2;
end = arrSize;
}

int sum = 0;
for(int i = start; i<end; i++){
   sum += arr[i]; 
}
printf("calculated partial sum: %d \n", sum);

if(id == 0){
//child
  close(fd[0]);
  if (write(fd[1], &sum, sizeof(sum)) == -1){
     return 3;
  }
  close(fd[1]); 
}else {
//parent
int sumFromChild;
  close(fd[1]);
  if (read(fd[0], &sumFromChild, sizeof(sumFromChild)) == -1){
     return 4;
  }
  close(fd[0]); 
  
  int totalSum = sum + sumFromChild;
  printf("Total sum is: %d \n", totalSum);
  wait(NULL);
}
return 0;
}
