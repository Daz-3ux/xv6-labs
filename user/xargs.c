#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

int main(int argc, char **argv)
{
  //char *command[MAXARG];
  //int cnt = 0;
  // for(int i = 1; i < argc; i++) {
  //   command[cnt++] = argv[i];
  // }
  // command[cnt] = '\0';
  int ret = fork();
  if(ret == 0) { // child
    //char *buf;
    

  }else { // parent
    exec("bin/echo", argv);
  }

  exit(0);
}