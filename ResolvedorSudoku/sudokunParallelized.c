#include "sudokun.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_n 8

pthread_mutex_t mutex;
pthread_mutex_t mutex2;
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
int check(int row, int column, int number, int**grid[rows][columns]) {
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

void solve(int row, int column, int **newgrid) {
    int static n = 0;

    if (n < nThreads) {
        n++;

        pthread_mutex_lock(&mutex2);

        int **newGrid[rows][columns];

        // create new grid for all threads
        newGrid = (int**)malloc(sizeof(int*)*rows);
        for (int i = 0; i < rows; i++){
            newGrid[i] = (int*)malloc(sizeof(int)*columns);
        }

        for (int row = 0; row < rows; row++) {
            for (int column = 0; column < columns; column++) {
                newGrid[row][column] = grid[row][column];
            }
        }
    }

    int* args = malloc(sizeof(int)*4);
    args[0] = 0;
    args[1] = 0;
    args[2] = newGrid[rows][columns];

    pthread_t thread;
    pthread_create(&thread, NULL, solve, (void*) args);
    pthread_join(thread, NULL);

    pthread_mutex_unlock(&mutex2);

    int number, attempt;

    if (row == rows) {
        print();
    } else {
        for (number = 1; number <= rows; number++) {
            if (check(row, column, number, newGrid[rows][columns])) {
                attempt = newgrid[row][column];
                newGrid[row][column] = number;
                if (column == columns - 1)
                    solve(row + 1, 0, newGrid[rows][columns]);
                else
                    solve(row, column + 1, newGrid[rows][columns]);
                newGrid[row][column] = attempt;
            }
        }
    }

    // if(done()) {
    //     pthread_exit(NULL);
    // free_newGrid(newGrid);
    // }
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

    pthread_mutex_init(&mutex, NULL);
    rows = size*size;
    columns = size*size;
    allocate_grid();
    convert(size, buf);

    //initialize threads
    pthread_t threads[nThreads];

    free_grid();
    pthread_mutex_destroy(&mutex);
    pthread_mutex_destroy(&mutex2);
}

void print() {
    int row, column;
    static int solutions = 0;

    printf("Solutions: %d\n", ++solutions);
    for (row = 0; row < rows; row++) {
        for (column = 0; column < columns; column++) {
            printf (" %d",grid[row][column]);
            if (column % columns == (columns - 1)) printf ("  ");
        }
        printf ("\n");
        if (row % rows == (rows - 1)) printf ("\n");
    }
}


