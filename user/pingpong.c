#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char **argv)
{
  int my_pipe[2];
  if(pipe(my_pipe) != 0) {
    printf("pipe error");
    exit(1);
  }

  int ret = fork();
  if(ret ==  0) { // child
    char buf[2];
    if(read(my_pipe[0], buf, sizeof(buf)) == 0) {
      printf("read error");
      exit(1);
    }
    printf("%d: received ping\n", getpid());
    memset(buf, 0, sizeof(buf));
    if(write(my_pipe[1], buf, sizeof(buf)) == 0) {
      printf("write error");
      exit(1);
    };


  }else { // parnet
    char str[2] = "a";
    if(write(my_pipe[1], str, sizeof(str)) == 0) {
      printf("write error");
      exit(1);
    };

    memset(str, 0, sizeof(str));
    if(read(my_pipe[0], str, sizeof(str)) == 0) {
      printf("read error");
      exit(1);
    }
    printf("%d: received pong\n", getpid());

    int status;
    wait(&status);
  }

  exit(0);
}