#include <cstdio>

#include "acm2snd.h"
#include "riffhdr.h"
#include "portable-utils.h"


int main(int argc, char **argv)
{
    if(argc < 3) {
        printf("Minimal usage: binary infile outfile.\n");
        return 1;
    }

    FILE *finp = fopen(argv[argc - 2], "rb");
    FILE *foutp = fopen(argv[argc - 1], "wb");
    unsigned char *memory;
    int samples_written;

    ConvertAcmWav(fileno(finp), -1, memory, samples_written, 0);

    fclose(finp);

    fwrite(memory, 1, samples_written + sizeof(RIFF_HEADER), foutp);

    if(memory) {
        delete[] memory;
        memory = NULL;
    }

    fclose(foutp);

    return 0;
}
