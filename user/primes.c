#include "kernel/types.h"
#include "user/user.h"

/*
1. use pipe and fork to set up the pipeline
2. The first process feeds the numbers 2 through 35 into the pipeline
3. The first process can stop at 35
*/
#define STDERR 2

#define READEND 0
#define WRITEEND 1

void printPrime(int *input, int count)
{
  if(count == 0) {
    return;
  }
  int mypipe[2];
  if(pipe(mypipe) < 0) {
    fprintf(STDERR, "primes: pipe error\n");
    exit(1);
  }
  int prime = *input;
  printf("prime %d\n", prime);

  char buff[4];
  if(fork() == 0) { // child
    close(mypipe[READEND]);
    for(int i = 0; i < count; i++) {
      write(mypipe[WRITEEND], (char*)(input+i), 4);
    }
    close(mypipe[WRITEEND]);
    exit(0);
  }else { // parnet
    close(mypipe[WRITEEND]);
    count = 0;
    while(read(mypipe[READEND], buff, 4) != 0) {
      int temp = *(int*)buff;
      if(temp % prime) {
        *input = temp;
        input++;
        count++;
      }
    }
    printPrime(input - count, count);
    close(mypipe[READEND]);
    wait((int*)0);
  }
}

int main(int argc, char **argv) {
  int intput[34];
  int cnt = 0;
  for(int i = 2; i < 36; i++){
    intput[cnt++] = i;
  }

  printPrime(intput, 34);

  exit(0);
}