#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"

int main(int argc, char **argv)
{
  int sleep_time = atoi(argv[1]);
  sleep(sleep_time);

  exit(0);
}