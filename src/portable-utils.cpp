#include "portable-utils.h"

#include <cstring>
#include <unistd.h>


int strstartswith(char const *str, char const *prefix)
{
  return strncmp(str, prefix, strlen(prefix)) == 0;
}

int filelength(int fd)
{
  off_t pos = lseek(fd, 0, SEEK_CUR);
  off_t length = lseek(fd, 0, SEEK_END);
  lseek(fd, pos, SEEK_SET);
  return length;
}

int tell(int fd)
{
  return lseek(fd, 0, SEEK_CUR);
}
