#include <cstdio>
#include <cstring>
#include <cctype>
#include <libgen.h>

#include "snd2acm.h"


static int strstartswith(char const *str, char const *prefix)
{
  return strncmp(str, prefix, strlen(prefix)) == 0;
}

int main(int argc, char **argv) {
  if(argc < 3) {
    printf("Minimal usage: binary infile outfile.\n");
    return 1;
  }

  for(int idx = 0; idx < argc - 2; ++idx) {
    for(char *ptr = argv[idx]; *ptr; ++ptr) {
      *ptr = tolower(*ptr);
    }
  }

  bool wavc_or_acm = false;

  if(strstartswith(basename(argv[0]), "snd2acm")) {
    wavc_or_acm = false;
  } else if(strstartswith(basename(argv[0]), "wav2acm")) {
    wavc_or_acm = false;
  } else if(strstartswith(basename(argv[0]), "snd2wavc")) {
    wavc_or_acm = true;
  } else if(strstartswith(basename(argv[0]), "wav2wavc")) {
    wavc_or_acm = true;
  } else {
    printf("Unknown binary name: %s\n", basename(argv[0]));
    return 1;
  }

  FILE *finp = fopen(argv[argc - 2], "rb");
  FILE *foutp = fopen(argv[argc - 1], "wb");

  ConvertWavAcm(fileno(finp), -1, foutp, wavc_or_acm);

  fclose(finp);
  fclose(foutp);

  return 0;
}
