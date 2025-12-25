#ifndef ZIPFILE_STUBS_H
#define ZIPFILE_STUBS_H
#include "doomtype.h"
#include <stdbool.h>
#include <stdint.h>
// dunno about the real value.
#define ZIP_STAT_SIZE 4096

typedef uint64_t zip_uint64_t;
typedef int64_t zip_int64_t;
typedef struct {
  bool valid;
  size_t size;
} zip_stat_t;

typedef struct {
} zip_file_t;

typedef struct zip_t zip_t;
typedef struct{
}zip_error_t;

extern enum {
    ZIP_FL_UNCHANGED,
    ZIP_RDONLY
} ZIP_FL_ENUM;

int zip_fread(zip_file_t* file, byte *buffer, zip_uint64_t size);
size_t zip_get_num_entries(zip_t* archive, int zip_opmode);
char* zip_get_name(zip_t* archive, size_t index, int zip_opmode );
void zip_stat_index(zip_t* archive, int index, int zip_opmode, zip_stat_t* status);
zip_file_t* zip_fopen_index(zip_t* archive, int index, int zip_opmode);
void zip_fclose(zip_file_t* zipped_file);
zip_t* zip_open(const char* file_name, int zip_opmode, int* error_code);
void zip_error_init_with_code(zip_error_t* error, int error_code);
char* zip_error_strerror(zip_error_t* error);
void zip_close(zip_t* archive);
#endif