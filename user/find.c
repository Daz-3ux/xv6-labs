#include "kernel/fs.h"
#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

#define STDERR 2

char *fmtname(char *path) {
  static char buf[DIRSIZ + 1];
  char *p;

  // Find first character after last slash
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name
  if (strlen(p) >= DIRSIZ) return p;
  memmove(buf, p, strlen(p));
  memset(buf + strlen(p), '\0', DIRSIZ - strlen(p));

  return buf;
}

void find(char *dir, char *fileName) {
  char buf[512];
  char *p;
  int fd;
  struct dirent de;
  struct stat st;

  if ((fd = open(dir, 0)) < 0) {
    fprintf(STDERR, "find: cannot open %s\n", dir);
    return;
  }

  if (fstat(fd, &st) < 0) {
    fprintf(STDERR, "find: cannot stat %s\n", dir);
    close(fd);
    return;
  }

  switch (st.type) {
    case T_FILE:
      if (strcmp(fileName, fmtname(dir)) == 0) {
        printf("%s\n", dir);
      }
      break;

    case T_DIR:
      if (strlen(dir) + 1 + DIRSIZ + 1 > sizeof(buf)) {
        printf("find: path too long\n");
        break;
      }
      strcpy(buf, dir);
      p = buf + strlen(buf);
      *p = '/';
      p++;  // 字符串最后加上了'/', 指向'/'的后面

      while (read(fd, &de, sizeof(de)) == sizeof(de)) {
        if (de.inum == 0) continue;
        memmove(p, de.name, DIRSIZ);
        p[DIRSIZ] = '\0';
        if (strcmp(buf + strlen(buf) - 2, "/.") == 0 ||
            strcmp(buf + strlen(buf) - 3, "/..") == 0)
          continue;
        find(buf, fileName);
      }
      break;
  }
  close(fd);
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Usage: find directory file\n");
  }
  find(argv[1], argv[2]);

  exit(0);
}