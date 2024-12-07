/* COMP 530: Benchmark Utility */

// PID: 730466078
// PID: 730481231
// I pledge the COMP530 honor code.

#include "utils.h"

int main(int argc, char **argv, char **envp) {

  int (*io_operation)() = io_write;

  int c;
  while ((c = getopt(argc, argv, "s:b:o:rx")) != -1) {
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
    case 'r':
      io_operation = io_read;
      break;
    case 'x':
      is_random = 1;
      srand(time(NULL));
      break;
    default:
      break;
    }
  }

  file_desc = open(output, O_RDWR | O_CREAT, 0644);

#ifdef __APPLE__
  fcntl(file_desc, F_NOCACHE, 1);

#endif

#ifdef __LINUX___
  posix_fadvise(file_desc, 0, 0, POSIX_FADV_DONTNEED);
  printf("Linun\n");
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
  struct timespec start, stop;
  clock_gettime(CLOCK_REALTIME, &start);
  for (int i = 0; i < GB / block_size; i++) {
    write(file_desc, buf, block_size);
    lseek(file_desc, stride, SEEK_CUR);
    if (is_random) {
      int rstride = rand() % 16;
      rstride = (int)pow(2.0, (double)rstride) * 4096;

      // if ((rand() % 8 + 1) % 3 == 0) {
      //   rstride /= -2;
      // }
      lseek(file_desc, rstride, SEEK_CUR);
    }
  }
  fsync(file_desc);

  clock_gettime(CLOCK_REALTIME, &stop);

  float sec, nsec;

  sec = stop.tv_sec - start.tv_sec;
  nsec = stop.tv_nsec - start.tv_nsec;

  double throughput = 1.0 / (sec + nsec / 1000000000);
  printf("%f\n", throughput);

  free(buf);

  return throughput;
}

int io_read() {
  struct timespec start, stop;
  clock_gettime(CLOCK_REALTIME, &start);
  for (int i = 0; i < GB / block_size; i++) {
    read(file_desc, buf, block_size);
    lseek(file_desc, stride, SEEK_CUR);
    if (is_random) {
      int rstride = rand() % 16;
      rstride = (int)pow(2.0, (double)rstride) * 4096;

      if ((rand() % 8 + 1) % 3 == 0) {
        rstride *= -1;
      }
      lseek(file_desc, rstride, SEEK_CUR);
    }
  }
  fsync(file_desc);

  clock_gettime(CLOCK_REALTIME, &stop);

  float sec, nsec;

  sec = stop.tv_sec - start.tv_sec;
  nsec = stop.tv_nsec - start.tv_nsec;

  double throughput = 1.0 / (sec + nsec / 1000000000);
  printf("%f\n", throughput);

  free(buf);

  return throughput;
}