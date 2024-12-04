#include "utils.h"

int main(int argc, char **argv, char **envp) {

  int (*io_operation)();

  int c;
  while ((c = getopt(argc, argv, "s:b:o:mr")) != -1) {
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
      break;
    case 'r':
      break;
    default:
      break;
    }
  }

  file_desc = open(output, O_RDWR | O_CREAT | O_DIRECT, 0644);
  buf = (char *)malloc(GB * sizeof(char));
  memset(buf, '1',
         GB); // buffer filled with single random char for the sake of testing

  time_t start, stop;
  start = time(NULL);
  for (int i = 0; i < GB / block_size; i++) {
    write(file_desc, buf, block_size);
    lseek(file_desc, stride, SEEK_CUR);
  }
  fsync(file_desc);

  stop = time(NULL);

  printf("Start: %ld, stop: %ld, dif %ld\n", start, stop, stop - start);

  double throughput = GB / ((stop - start) / 1000);
  printf("Throughput = %f gb/s\n", throughput);

  free(buf);
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