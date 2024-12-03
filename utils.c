#include "utils.h"

int main(int argc, char **argv, char **envp) {

  int c;
  while (c = getopt(argc, argv, "s:b:o:r")) {
    switch (c) {
    case 's':

    case 'b':

    case 'o':

    case 'r':

    default:
      break;
    }
  }

  file_desc = open("dummy", O_RDWR | O_CREAT, 0644);
  buf = (char *)malloc(GB * sizeof(char));
  memset(buf, '0', GB);

  for (int i = 0; i < GB / block_size; i++) {
    write(file_desc, buf, block_size);
    lseek(file_desc, stride, SEEK_CUR);
  }
}