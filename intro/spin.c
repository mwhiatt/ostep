#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "common.h"

int main (int argc, char *argv[]) {
  if (argc != 3) {
    printf("improper usage\n");
    exit(1);
  }

  char *str = argv[1];

  int howlong = atoi(argv[2]);
  while(1) {
    printf("%s\n", str);
    Spin(howlong);
  }
  return 0;
}