#include "kernel/types.h"
#include "user/user.h"

#define STDERR 2

#define EXIT_SUCCESS 0

#define READEND 0
#define WRITEEND 1

void sieve(int pleft[2]) {
  int num;
  read(pleft[READEND], &num, sizeof(num));
  if (num == -1) {
    return;
  }
  printf("prime %d\n", num);

  int pright[2];
  int ret = pipe(pright);
  if (ret < 0) {
    fprintf(STDERR, "primes: pipe error\n");
  }

  ret = fork();
  if (ret == 0) {  // child
    close(pright[WRITEEND]);
    close(pleft[READEND]);
    sieve(pright);
  } else {  // parent
    close(pright[READEND]);
    int buf;
    while(read(pleft[READEND], &buf, sizeof(buf)) && buf != -1) {
      if (buf % num) {
        write(pright[WRITEEND], &buf, sizeof(buf));
      }
    }
    buf = -1;
    write(pright[WRITEEND], &buf, sizeof(buf));

    wait((int *)0);
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char **argv) {
  int input_pipe[2];
  int ret = pipe(input_pipe);
  if (ret < 0) {
    fprintf(STDERR, "primes: pipe error\n");
  }

  ret = fork();
  if (ret == 0) {  // child
    close(input_pipe[WRITEEND]);
    sieve(input_pipe);
    exit(EXIT_SUCCESS);
  } else {  // parent
    close(input_pipe[READEND]);
    for (int i = 2; i <= 35; i++) {
      write(input_pipe[WRITEEND], &i, sizeof(i));
    }
    int guard = -1;
    write(input_pipe[WRITEEND], &guard, sizeof(guard));

    close(input_pipe[WRITEEND]);
    wait((int *)0);
  }

  exit(EXIT_SUCCESS);
}