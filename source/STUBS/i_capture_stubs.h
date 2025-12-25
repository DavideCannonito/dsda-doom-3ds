#ifndef I_CAPTURE_STUBS_H
#define I_CAPTURE_STUBS_H

int pipe(int *something);
int fork();
//void dup2(int fd, int opmode);
//void close(int fd);
void _exit(int retnum);
void waitpid(int pid, int *something, int returncode);
// i have no idea if ... is appropriate
int execl(const char* command,const char* something, ...);
extern enum {
  STDIN_FILENO,
  STDOUT_FILENO,
  STDERR_FILENO,
} STDOUT_IN_ERR_ENUM;
#endif