#include "sudokun.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_n 8

void print(int size, int grid[][size*size]) {
    static int solutions = 0;
    int line, column;

    printf("Solução: %d\n", ++solutions);
        for (line = 0; line < size * size; line++) {
            for (column = 0; column  < size * size; column++) {
                printf(" %d", grid[line][column]);
                if (column % size == 0) 
                    printf("  ");
            }
            printf("\n");
            if (line % size == 0)
                printf("\n");
        }
}

int isValid(int line, int column, int number, int size, int grid[][size * size]) {
        int i, j, localLine, localColumn;

        if (grid[line][column] == number)
            return 1;
        if (grid[line][column] != 0)
            return 0;
        for (i = 0; i < size * size; i++) {
            if (grid[line][i] == number)
                return 0;
        }
        for (j = 0; j < size * size; j++) {
            if(grid[j][column] == number)
                return 0;
        }

        localLine = line/size;
        localColumn = column/size;

        for (i = localLine * size; i < (localLine + 1) * size; i++) {
            for (j = localColumn * size; j < (localColumn + 1) * size; j++) {
                if(grid[i][j] == number)
                    return 0;
            }
        }

    return 1;
}

void solveSudoku(int line, int column, int size, int grid[][size*size]) {
    int number, temp;

    if (line == 9)
        print(size, grid);
    else
        for (number = 1; number <= size * size; number++) {
            if (isValid(line, column, number, size, grid)) {
                temp = grid[line][column];
                grid[line][column] = number;

                if (column == (size * size) - 1)
                    solveSudoku(line + 1, 0, size, grid);
                else
                    solveSudoku(line, column + 1, size, grid);
                grid[line][column] = temp;
            }
        }
}


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

  int line = size * size;
  int column = size * size;
  int grid[line][column];

    for (int i = 0; i < size * size; i++) {
        for (int j = 0; j < size * size; j++) {
            grid[line][column] = buf[i * (size * size) + j];
        }
    }

  solveSudoku(0, 0, size, grid);

  return 0;
}
