#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

/*
1. use pipe and fork to set up the pipeline
2. The first process feeds the numbers 2 through 35 into the pipeline
3. The first process can stop at 35
4.
*/

int main(int argc, char **argv) {
  int num[33];
  memset(num, 0, sizeof(num));
  for (int i = 0; i < 33; i++) {
    int myNum = 2;
    num[i] = myNum;
    myNum++;
  }


  exit(0);
}