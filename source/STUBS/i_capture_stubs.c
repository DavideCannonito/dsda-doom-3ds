#include "i_capture_stubs.h"
int pipe(int* something)
{
    return -1;
}

int fork()
{
    return -1;
}

/*void dup2(int fd, int opmode){
    return;
}*/

/*void close(int fd){
    return;
}*/

// i have no idea if ... is appropriate
int execl(const char* command,const char* something, ...){
    return -1;
}

void _exit(int retnum){
    return;
}

void waitpid(int pid, int* something, int returncode){
    return;
}