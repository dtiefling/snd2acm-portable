#ifndef _UH_PORTABLE_UTILS_H
#define _UH_PORTABLE_UTILS_H

typedef unsigned char BYTE;

int strstartswith(char const *str, char const *prefix);

int filelength(int fd);

int tell(int fd);

#endif
