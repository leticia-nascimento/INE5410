#include "sudokun.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#define MAX_n 8

int **grid;
int rows, columns;

int allocate_grid() {
    grid = (int**)malloc(sizeof(int*)*rows);
    int i;

    for (i = 0; i < rows; i++)
        grid[i] = (int*)malloc(sizeof(int)*columns);
    
    return grid;
}

void free_grid() {
    int i;

    for (i = 0; i < rows; i++)
        free(grid[i]);

    free(grid);
}

void convert(int size, int buf[]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            grid[i][j] = buf[i * (size*size) + j];
        }
    }
    solve(0,0);
}

// checks if a number belongs to a cell
int check(int row, int column, int number) {
    int square = (int)(sqrt(rows));

    if (grid[row][column] == number) return 1;
    if (grid[row][column] != 0) return 0;

    for (int j = 0; j < columns; j++)
        if (grid[row][j] == number) return 0;

    for (int i = 0; i < rows; i++)
        if (grid[i][column] == number) return 0;

    int sector_row = row / square;
    int sector_column = column / square;

    for (int i = sector_row * square; i < (sector_row + 1) * square; ++i)
        for (int j = sector_column * square; j < (sector_column + 1) * square; ++j)
            if (grid[i][j] == number) return 0;

    return 1;
}

void solve(int row, int column) {
    int number, attempt;

    if (row == rows) {
        print();
    } else {
        for (number = 1; number <= rows; number++) {
            if (check(row, column, number)) {
                attempt = grid[row][column];
                grid[row][column] = number;
                if (column == columns - 1)
                    solve(row + 1, 0);
                else
                    solve(row, column + 1);
                grid[row][column] = attempt;
            }
        }
    }
}


int main(int argc, char argv) {
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

    rows = size*size;
    columns = size*size;
    allocate_grid();
    convert(size, buf);
    free_grid();
    // printBuf(buf, size);
}

void print() {
    int row, column;
    static int solutions = 0;

    printf("Solutions: %d\n", ++solutions);
    for (row = 0; row < rows; row++) {
        for (column = 0; column < columns; column++) {
            printf (" %d",grid[row][column]);
            // xx
            if (column % columns == (columns - 1)) printf ("  ");
        }
        //xx
        printf ("\n");
        if (row % rows == (rows - 1)) printf ("\n");
    }
}

void printBuf(int buf[], int size) {
    int size_squared = size * size;
    printf("This is the buf\n");
    for (int i = 0; i < size_squared; i++) {
        for (int j = 0; j < size_squared; j++)
        printf(" %d ", buf[i * size_squared + j]);

        printf("\n");
    }
}

