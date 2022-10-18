#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "kernel/param.h"
#include "user/user.h"

#define MSGSIZE 32

#define EXIT_SUCCESS 0

int main(int argc, char **argv)
{
  sleep(10);
  // 获取前一个命令的标准输出
  char preBuffer[MSGSIZE];
  read(0, preBuffer, sizeof(preBuffer));

  // 获取自己的命令行参数
  char *xargv[MAXARG];
  int xargc = 0;
  for(int i = 1; i < argc; i++){
    xargv[xargc] = argv[i];
    xargc++;
  }

  char *p = preBuffer;
  for(int i = 0; i < MAXARG; i++){
    if(preBuffer[i] == '\n') {
      int pid = fork();
      if(pid == 0) { // child
        preBuffer[i] = '\0';
        xargv[xargc++] = p;
        xargv[xargc] = '\0';
        argc -= 2;

        exec(xargv[0], xargv);
        exit(EXIT_SUCCESS);
      }else { // parent
        p = &preBuffer[i+1];
        wait((int*)0);
      }
    }
  }
  
  exit(EXIT_SUCCESS);
}