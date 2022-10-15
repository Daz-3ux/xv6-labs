#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv)
{
  int mypipe[2];
  if(pipe(mypipe) < 0){
    printf("pipe error");
    exit(1);
  }
  int ret_fork = fork();
  if(ret_fork != 0) {

  }

  exit(0);
}