#include "sudokun.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_n 8

int nThreads = 4;

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

void free_newGrid(int **newgrid) {
    int i;

    for (i = 0; i < rows; i++)
        free(newgrid[i]);

    free(newgrid);
}

void convert(int size, int buf[]) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            grid[i][j] = buf[i * (size*size) + j];
        }
    }
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

void* thrWork(void *ide) {
    // int* id = (int*)ide;
    int id = atoi(ide);
    printf("%d\n", id);
    // int id = (int) arg;
    int row, column;
    int row2, column2;

    // printf("%s\n", id );

    // create new grid for all threads
    int **newGrid = (int**)malloc(sizeof(int*)*rows);
    for (int k = 0; k < rows; k++)
        newGrid[k] = (int*)malloc(sizeof(int)*columns);
    for (row = 0; row < rows; row++) {
        for (column = 0; column < columns; column++) {
            newGrid[row][column] = grid[row][column];
    }

    // find 0
    if(0 == 0) {
        for (row2 = 0; row2 < rows; row2++) {
            for (column2 = 0; column2 < columns; column2++) {
                if(newGrid[row2][column2] == 0) {
                    // printf("%d, %d \n", row2, column2);
                    break;
                }
            //     printf (" %d",newGrid[row2][column2]);
            //     // xx
            //     if (column2 % columns == (columns - 1)) printf ("  ");
            // }
            // //xx
            // printf ("\n");
            // if (row2 % rows == (rows - 1)) printf ("\n");
            }
        }
        // printf("%d, %d \n", row2, column2);
    }

    pthread_exit(NULL);
    free_newGrid(newGrid);
    }   
}

int main(int argc, char **argv) {
    // verifica argumento (número de threads)
    if (argc == 2) {
        nThreads = atoi(argv[1]);
        if (nThreads < 1) {
            printf("Erro: Número de threads deve ser positivo.\n");
            return 0;
        }
    }

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

    //initialize threads
    pthread_t threads[nThreads];
    int a;
    for (a = 0; a < nThreads; a++) {
        pthread_create(&threads[a], NULL, thrWork, (void*)threads[a]);
    }

    int b;
    for (b = 0; b < nThreads; b++) {
        pthread_join(threads[b], NULL);
    }

    free_grid();
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


