#include "zipfile_stubs.h"

int zip_fread(zip_file_t* file, byte *buffer, zip_uint64_t size){
    return 0;
}

size_t zip_get_num_entries(zip_t* archive, int zip_opmode){
    return 0;
}

char* zip_get_name(zip_t* archive, size_t index, int zip_opmode ){
    return "CHANGEME_zip_get_name";
}

void zip_stat_index(zip_t* archive, int index, int zip_opmode, zip_stat_t* status){
    return;
}

zip_file_t* zip_fopen_index(zip_t* archive, int index, int zip_opmode){
    return NULL;
}

void zip_fclose(zip_file_t* zipped_file){
    return;
}

zip_t* zip_open(const char* file_name, int zip_opmode, int* error_code){
    return NULL;
}

void zip_error_init_with_code(zip_error_t* error, int error_code){
    return;
}

char* zip_error_strerror(zip_error_t* error){
    return "CHANGEME_zip_error_strerror";
}

void zip_close(zip_t* archive){
    return;
}