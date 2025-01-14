#include "stdafx.h"
// snd2acm converter.

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#if _MSC_VER
#include <windows.h>
#include <io.h>
#endif
#include "subband.h"
#include "readers.h"
#include "packer.h"
#include "general.h"
#include "riffhdr.h"

#define HATCH_SIZE 655360
#define COMPRESSION_RATE 100.0

#if !_MSC_VER
#include <unistd.h>

static int filelength(int fd)
{
  off_t pos = lseek(fd, 0, SEEK_CUR);
  off_t length = lseek(fd, 0, SEEK_END);
  lseek(fd, pos, SEEK_SET);
  return length;
}
#endif

int fhandle;
FILE *out_file = NULL;
CSubbandCoder* coder = NULL;
CSoundReader* reader = NULL;
CValuePacker* packer = NULL;
int levels = 7, f_len = 11, subblocks = 16;
int reader_type = SND_READER_AUTO;
char tp = 'O';
short* input_samples = NULL;
int32_t* coeffs = NULL;
short* block_to_pack = NULL;
int32_t block_size, sb_size, samples;
double bps_limit;

bool set_type(char type)
{
  if(type=='D' || type=='O') { tp=type; return true; }
  return false;
}

int init(int maxlen, bool wavc_or_acm) {
  reader = CreateSoundReader (fhandle, reader_type, maxlen);
  if(!reader) {
    return 0;
  }

	if (tp == 'D') {
		coder = new C_DRZF_SubbandCoder (f_len, levels);
	} else if (tp == 'O') {
		coder = new C_DOpt_SubbandCoder (f_len, levels);
	}
	if ( !coder || !coder->init_filter() ) {
		return 0;
	}

	samples = reader->get_samples_left();
	sb_size = 1 << levels;
	block_size = sb_size * subblocks;
	ACM_Header hdr = {IP_ACM_SIG, 0, (unsigned short) reader->get_channels(), (unsigned short) reader->get_samplerate(), 0, 0};
	hdr. samples = samples;
	hdr. levels = levels;
	hdr. subblocks = subblocks;
  if(wavc_or_acm) write_wavc_header(out_file, samples, reader->get_channels(), 0, reader->get_samplerate());
	fwrite (&hdr, 1, sizeof(hdr), out_file);

	bps_limit =COMPRESSION_RATE*((double)reader->get_bits()*samples/ceil((double)samples/block_size)/100.0);

	packer = new CValuePacker (out_file, subblocks, sb_size, (int32_t) bps_limit);
	if ( !packer || !packer->init_packer() ) {
		return 0;
	}

	input_samples = new short [HATCH_SIZE];
	coeffs = new int32_t [HATCH_SIZE];
	block_to_pack = new short [block_size];
	if ( !input_samples || !coeffs || !block_to_pack) {
		return 0;
	};
	return 1;
}
void finalize2() {
	if (packer) delete packer;
	if (coder) delete coder;
	if (reader) delete reader;
	if (input_samples) delete input_samples;
	if (coeffs) delete coeffs;
	if (block_to_pack) delete block_to_pack;
}

int ConvertWavAcm(int fh, int32_t maxlen, FILE *foutp, bool wavc_or_acm)
{
//  bps_limit=-1.0;
  try {
    //Since snd2acm handled arguments using parse_args...
    if(maxlen<0) maxlen=filelength(fh);
    out_file=foutp;
    reader_type=SND_READER_WAV; //Sound reader type
    fhandle=fh;
    if (!init(maxlen, wavc_or_acm)) {
      finalize2();
      return 1;
    }
    
    //Actual decoding section, with printf's removed
    int32_t left_to_pack = (int32_t)ceil((double)samples/block_size)*block_size;
    short* cur_block_pos = block_to_pack;
    int32_t ready_to_pack = 0;
    int32_t* tmp_coeffs_pos;
    int32_t left_to_filter = samples + coder->get_init_size();
    int32_t warnings = 0, max_minus_warn = 0, max_plus_warn = 0, i;
    while (left_to_filter > 0) {
      // reading samples and filtering them
      int32_t next_portion = (left_to_filter > HATCH_SIZE)? HATCH_SIZE: left_to_filter;
      reader->read_samples (input_samples, next_portion);
      int32_t coeffs_gained = coder->filter_data (input_samples, next_portion, coeffs);
      
      // transferring the coefficients into block
      for (i=0, tmp_coeffs_pos = coeffs; i<coeffs_gained; i++, tmp_coeffs_pos++) {
        if (*tmp_coeffs_pos > 32767) {
          *cur_block_pos = 32767;
          warnings++;
          if (*tmp_coeffs_pos > max_plus_warn) max_plus_warn = *tmp_coeffs_pos;
        } else if (*tmp_coeffs_pos < -32768) {
          *cur_block_pos = -32768;
          warnings++;
          if (*tmp_coeffs_pos < max_minus_warn) max_minus_warn = *tmp_coeffs_pos;
        } else
          *cur_block_pos = (short) *tmp_coeffs_pos;
        ready_to_pack++;
        cur_block_pos++;
        if (ready_to_pack == block_size) {
          // next block is ready to pack, so pack it
          packer->add_one_block (block_to_pack);
          ready_to_pack = 0;
          cur_block_pos = block_to_pack;
          left_to_pack -= block_size;
        }
      }
      left_to_filter -= next_portion;
    }
    // at this point the block can be incompletely filled, we need to fill it with zero, and pack
    if (ready_to_pack) {
      memset (cur_block_pos, 0, (block_size-ready_to_pack)*sizeof(short));
      packer->add_one_block (block_to_pack);
      left_to_pack -= block_size;
    }
    
    int32_t bytes_resulted = packer->flush_bit_stream() + sizeof (ACM_Header);
    
    if(wavc_or_acm)
    {
      write_wavc_header(foutp, samples, reader->get_channels(), bytes_resulted, reader->get_samplerate());
    }
    finalize2();
    return 0;
  }
  catch(...)
  {
    return 4;
  }
}

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
