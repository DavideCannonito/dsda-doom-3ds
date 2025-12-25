#include "i_sndfile_stubs.h"
SNDFILE *sf_open_virtual(SF_VIRTUAL_IO *sfvio, int sfm_operation,
                         SF_INFO *sf_info, MEMFILE *sfdata) {
  return NULL;
}

char *sf_strerror(SNDFILE *sndfile) { return "CHANGEME_sf_strerror"; }

void sf_close(SNDFILE *sndfile) { return; }

sf_count_t sf_readf_float(SNDFILE *sndfile, void *function, size_t frames) {
  return 0;
}

sf_count_t sf_readf_short(SNDFILE *sndfile, void *function, size_t frames) {
  return 0;
}