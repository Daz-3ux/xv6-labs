#include "kernel/types.h"
#include "user/user.h"

#define WRITEEND 1
#define READEND 0

int main(int argc, char **argv) {
  int pfd[2];
  int cfd[2];

  char buf[16];
  int pid;

  if ((pipe(pfd) != 0) || (pipe(cfd) != 0)) {
    printf("Error: pipe failed");
    exit(1);
  }

  if ((pid = fork()) < 0) {
    printf("Error: fork failed");
    exit(1);
  } else if (pid == 0) {  // child
    close(pfd[WRITEEND]);
    close(cfd[READEND]);
    read(pfd[READEND], buf, sizeof(buf));
    printf("%d: received %s\n", getpid(), buf);
    write(cfd[WRITEEND], "pong", 4);
    close(cfd[WRITEEND]);
  } else {  // parents
    close(pfd[READEND]);
    close(cfd[WRITEEND]);
    write(pfd[WRITEEND], "ping", 4);
    close(pfd[WRITEEND]);
    read(cfd[READEND], buf, sizeof(buf));
    printf("%d: received %s\n", getpid(), buf);
  }

  exit(0);
}