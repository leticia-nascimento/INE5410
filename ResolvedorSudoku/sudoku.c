#include "sudokun.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_n 8

int main (int argc, char **argv) {
  int size;
  assert(scanf("%d", &size) == 1);
  assert (size <= MAX_n);

  int lines = size * size;
  int columns = size * size;
  int buf[lines][columns];

  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < columns; j++) {
      if (scanf("%d", &buf[i][j]) != 1) {
        printf("error reading file (%d)(%d)\n", i,j);
        exit(1);
      }
    }
  }

  print_grid(lines, columns,buf[lines][columns]);

  return 0;
}

void print_grid(int lines, int columns, int buf[lines][columns]) {
  for (int i = 0; i < lines; i++) {
    for (int j = 0; j < columns; j++)
      printf("%d ", &buf[lines][columns]);

    printf("\n");
  }
}
