// manually generated from the originally found cmake/config.h.cin file and
// cross referencing from CMakeLists.txt
#define PROJECT_NAME "dsda-doom"
#define PROJECT_TARNAME "dsda-doom"
#define WAD_DATA "dsda-doom.wad"
#define PROJECT_VERSION "0.29.4"
#define PROJECT_STRING "dsda-doom 0.29.4"
// dunno what these 2 are for
#define DOOMWADDIR "@DOOMWADDIR@"
#define DSDA_ABSOLUTE_PWAD_PATH "@DSDA_ABSOLUTE_PWAD_PATH@"

#define HAVE_GETOPT
#define HAVE_MMAP
#define HAVE_CREATE_FILE_MAPPING
#define HAVE_STRSIGNAL
#define HAVE_MKSTEMP
#define HAVE_GETPWUID
#define HAVE_SYS_WAIT_H
#define HAVE_UNISTD_H
#define HAVE_DIRENT_H
// renamed from HAVE_LIBSDL2_IMAGE because devkitpro's ported library is
// SDL_image 1.2
#define HAVE_LIBSDL_IMAGE
#define HAVE_LIBMAD
#define HAVE_LIBXMP
#define HAVE_LIBVORBISFILE

// want all the checks
#define RANGECHECK

// can't find it in 3ds-portlibs group
#undef HAVE_SNDFILE_MPEG
// want all the checks
#undef SIMPLECHECKS
// can't find it in 3ds-portlibs group
#undef HAVE_LIBPORTMIDI
// 3DS' ARM processor is in little endian... i think
#undef WORDS_BIGENDIAN
// gives missing header errors so i think it's not there
#undef HAVE_ASM_BYTEORDER_H
// we have wildmidi at home. TODO: see if it's possible to use
#undef HAVE_LIBFLUIDSYNTH