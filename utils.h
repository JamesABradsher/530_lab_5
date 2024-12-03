#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define GB 1024 * 1024 * 1024
#define MB 1024 * 1024
#define KB 1024

int file_desc;
char *buf;

int stride = 0;
int block_size = 4 * KB;

#endif
