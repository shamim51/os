#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void collatz(int n){
   if(fork()==0){
      printf("Child is on process...\n");
      printf("%d ,",n);
      while(n!=1){
         if(n%2==0){
            n/=2;
         }
         else{
            n=3*n+1;
         }
         printf("%d ,",n);
      }
      printf("\b \nChild is exiting...\n");
      exit(0);
   }
   else{
      wait(NULL);
      printf("Parent process is done.\n");
   }
}

int main(int argc, char *argv[]){
      if(argc!=2 || atoi(argv[1])<1){
         printf("Enter valid input (n>0)\n");
      }
      else{
         collatz(atoi(argv[1]));
   }
}

/*
gcc -o A A.c
.A 9
*/
