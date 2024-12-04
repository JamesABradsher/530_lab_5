#include "utils.h"

int main(int argc, char **argv, char **envp) {

  int (*io_operation)() = io_write;

  int c;
  while ((c = getopt(argc, argv, "s:b:o:m:r")) != -1) {
    switch (c) {
    case 's':
      stride = process_opt(optarg);
      break;
    case 'b':
      block_size = process_opt(optarg);
      break;
    case 'o':
      output = strdup(optarg);
      break;
    case 'm':
      if (strcmp(optarg, "r") == 0) {
        printf("reading\n");
        io_operation = io_read;
      }
      break;
    case 'r':
      break;
    default:
      break;
    }
  }

  io_fd = open(output, O_RDWR | O_CREAT, 0644);

#ifdef __APPLE__
  fcntl(io_fd, F_NOCACHE, 1);
#endif
  buf = (char *)malloc(GB * sizeof(char));
  memset(buf, '1',
         GB); // buffer filled with single random char for the sake of testing

  io_operation();
}

int process_opt(char *opt) {
  int rv = atoi(opt);
  int mult = 1;
  int i = 0;
  char c = opt[i];

  while (c != 'k' && c != 'm' && c != '\0') {
    c = opt[++i];
  }

  if (c == 'k') {
    mult = KB;
  } else if (c == 'm') {
    mult = MB;
  }

  rv *= mult;

  // bounds checking rv between 4kb and 100mb
  rv = rv < 4 * KB ? 4 * KB : rv;
  rv = rv > 100 * MB ? 100 * MB : rv;

  return rv;
}

int io_write() {
  time_t start, stop;
  start = time(NULL);
  for (int i = 0; i < GB / block_size; i++) {
    write(file_desc, buf, block_size);
    lseek(file_desc, stride, SEEK_CUR);
  }
  fsync(file_desc);

  stop = time(NULL);

  printf("Start: %ld, stop: %ld, dif %ld\n", start, stop, stop - start);

  double throughput = 1.07 / ((stop - start));
  printf("Throughput = %f gb/s\n", throughput);

  free(buf);

  return throughput;
}

int io_read() {
  printf("very busy\n");
  return 0;
}