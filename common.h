#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/ioctl.h>
#include <netdb.h>
#include <stdio.h>

#define SERVER_PORT 8080
#define MAX_LINE 4096
#define SA struct sockaddr
#define MAX_LEN 256

void black();
void red();
void yellow();
void blue();
void green();
void purple();

void black() {printf("\033[1;30m");}
void red() {printf("\033[1;31m");}
void green() {printf("\033[1;32m");}
void blue() {printf("\033[1;34m");}
void yellow() {printf("\033[1;33m");}
void purple() {printf("\033[1;35m");}
void reset() {printf("\033[0m");}



void err_n_die(const char *fmt, ...);
char *bin2hex(const unsigned char *input, size_t len);
