#ifndef UTILS_H
#define UTILS_H

#include <fcntl.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define GB 1024 * 1024 * 1024
#define MB 1024 * 1024
#define KB 1024

int file_desc;
char *buf;
char *output = "dummy.txt";

int stride = 0;
int block_size = 4 * KB;
int is_random = 0;

int process_opt(char *);
int io_read();
int io_write();

#endif
