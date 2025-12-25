#ifndef I_SNDFILE_STUBS_H
#define I_SNDFILE_STUBS_H
#include "memio.h"
#include <stddef.h>
#include <stdint.h>
typedef long int sf_count_t;

typedef struct {

} SNDFILE;

typedef struct {
  void *data;
  uint8_t format;
  size_t frames;
  uint8_t channels;
  uint32_t samplerate;
} SF_INFO;

typedef struct {
  void *functionptr1;
  void *functionptr2;
  void *functionptr3;
  void *functionptr4;
  void *functionptr5;
} SF_VIRTUAL_IO;

extern enum {
  SFM_READ,
  SF_FORMAT_SUBMASK,
  SF_FORMAT_PCM_24,
  SF_FORMAT_PCM_32,
  SF_FORMAT_FLOAT,
  SF_FORMAT_DOUBLE,
  SF_FORMAT_VORBIS,
  SF_FORMAT_OPUS,
  SF_FORMAT_ALAC_20,
  SF_FORMAT_ALAC_24,
  SF_FORMAT_ALAC_32,
} SFM_ENUM;

SNDFILE *sf_open_virtual(SF_VIRTUAL_IO *sfvio, int sfm_operation,
                         SF_INFO *sf_info, MEMFILE *sfdata);
char *sf_strerror(SNDFILE *sndfile);
void sf_close(SNDFILE *sndfile);
sf_count_t sf_readf_float(SNDFILE* sndfile,void* function, size_t frames);
sf_count_t sf_readf_short(SNDFILE* sndfile,void* function, size_t frames);
#endif
