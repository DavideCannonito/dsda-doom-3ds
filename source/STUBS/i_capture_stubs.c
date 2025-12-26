#include "i_capture_stubs.h"
int pipe(int* something)
{
    return -1;
}
// these are present in the 3DS libraries. Do not stub them, or else evil segfault appears
// int fork()
// {
//     return -1;
// }
// these are present in the 3DS libraries. Do not stub them, or else evil segfault appears
// void dup2(int fd, int opmode){
//     return;
// }
// these are present in the 3DS libraries. Do not stub them, or else evil segfault appears
// void close(int fd){
//     return;
// }

// // i have no idea if ... is appropriate
int execl(const char* command,const char* something, ...){
    return -1;
}
// these are present in the 3DS libraries. Do not stub them, or else evil segfault appears
// void _exit(int retnum){
//     return;
// }

void waitpid(int pid, int* something, int returncode){
    return;
}