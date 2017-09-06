#include "sudokun.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_n 8

int main (int argc, char **argv) {
  int size;
  assert(scanf("%d", &size) == 1);
  assert (size <= MAX_n);

  int buf_size = size * size * size * size;
  int buf[buf_size];

  for (int i = 0; i < buf_size; i++) {
    if (scanf("%d", &buf[i]) != 1) {
      printf("error reading file (%d)\n", i);
      exit(1);
    }
  }

  print_grid(buf, size);

  return 0;
}

void print_grid(int buf[], int size) {
  int size_squared = size * size;

  for (int i = 0; i < size_squared; i++) {
    for (int j = 0; j < size_squared; j++)
      printf("%d ", buf[i * size_squared + j]);

    printf("\n");
  }
}
