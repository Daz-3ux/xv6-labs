#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

/*
1. Write a simple version of the UNIX find program: find all the files in a directory tree with a specific name
2. Look at user/ls.c to see how to read directories.
3. Use recursion to allow find to descend into sub-directories.
4. Don't recurse into "." and "..".
5. Changes to the file system persist across runs of qemu; to get a clean file system run make clean and then make qemu.
6. Use strcmp().
*/

/*
  $ make qemu
  ...
  init: starting sh
  $ echo > b
  $ mkdir a
  $ echo > a/b
  $ find . b
  ./b
  ./a/b
  $ 
*/


int main(int argc, char **argv) {
  
}