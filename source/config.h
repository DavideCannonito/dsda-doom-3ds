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
#define HAVE_STRSIGNAL
#define HAVE_MKSTEMP
#define HAVE_GETPWUID
#define HAVE_SYS_WAIT_H
#define HAVE_UNISTD_H
#define HAVE_DIRENT_H
// --renamed from HAVE_LIBSDL2_IMAGE because devkitpro's ported library is
// SDL_image 1.2-- scratch this, we have SDL2 now 8)
#define HAVE_LIBSDL2_IMAGE
#define HAVE_LIBMAD
#define HAVE_LIBXMP
// TEMPORARILY DISABLE LIBVORBISFILE. There is a function that isn't present in portlibs.
#undef HAVE_LIBVORBISFILE

// want all the checks - TEMPORARILY DISABLED. FIXME: NEED TO HUNT DOWN AN UNDEFINED "VIDEO" VARIABLE (r_drawflush.inl)
#undef RANGECHECK

// if needed, will find a replacement. mmap() doesn't exist for 3DS. Might need to create a wrapper that uses svcControlMemory()?
#undef HAVE_MMAP
// the CMakeLists.txt file has this and HAVE_MMAP paired. Maybe there is an implementation that gets away from using mmap()
#undef HAVE_CREATE_FILE_MAPPING
// can't find it in 3ds-portlibs group
#undef HAVE_SNDFILE_MPEG
// want all the checks - TEMPORARILY DISABLED. FIXME: NEED TO HUNT DOWN AN UNDEFINED "VIDEO" VARIABLE (r_drawflush.inl)
#define SIMPLECHECKS
// can't find it in 3ds-portlibs group
#undef HAVE_LIBPORTMIDI
// 3DS' ARM processor is in little endian... i think
#undef WORDS_BIGENDIAN
// gives missing header errors so i think it's not there
#undef HAVE_ASM_BYTEORDER_H
// we have wildmidi at home. TODO: see if it's possible to use
#undef HAVE_LIBFLUIDSYNTH
// personally added - remove libsndfile stuff
#undef HAVE_LIBSNDFILE
// personally added - not sure this port will ever need libzip, and there is no ported version of libzip
#undef HAVE_LIBZIP
// personally added - just to stub OpenGL/HW rendering stuff
#undef HAVE_GRAPHICS