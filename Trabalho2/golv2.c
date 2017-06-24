/*
* The Game of Life
*
* a cell is born, if it has exactly three neighbours
* a cell dies of loneliness, if it has less than two neighbours
* a cell dies of overcrowding, if it has more than three neighbours
* a cell survives to the next generation, if it does not die of loneliness
* or overcrowding
*
* In this version, a 2D array of ints is used.  A 1 cell is on, a 0 cell is off.
* The game plays a number of steps (given by the input), printing to the screen each time.  'x' printed
* means on, space means off.
*
*/
#include <stdio.h>
#include <stdlib.h>

typedef unsigned char cell_t;

int size, steps;
//int nprocs, rank;

cell_t* allocate_board (int size) {
  cell_t* board = (cell_t*) malloc(sizeof(cell_t*)*size*size);
  return board;
}

void free_board (cell_t* board) {
  free(board);
}

/* return the number of on cells adjacent to the i,j cell */
int adjacent_to (cell_t* board, int size, int i, int j) {
  int k, l, count=0;

  int sk = i-1;
  int ek = i+1;
  int sl = j-1;
  int el = j+1;

  for (k=sk; k<=ek; k++) {
    for (l=sl; l<=el; l++) {
        count+=board[k*size + l];
    }
  }
  count-=board[i*size + j];

  return count;
}

void play (cell_t* board, cell_t* newboard, int size) {
  int   i, j, a;
  /* for each cell, apply the rules of Life */
  for (i=1; i<size-1; i++) {
    for (j=1; j<size-1; j++) {
        a = adjacent_to (board, size, i, j);
        if (a == 2) newboard[i*size + j] = board[i*size + j];
        if (a == 3) newboard[i*size + j] = 1;
        if (a < 2) newboard[i*size + j] = 0;
        if (a > 3) newboard[i*size + j] = 0;
    }
  }
}

/* print the life board */
void print (cell_t* board, int size) {
  int   i, j;
  /* for each row */
  for (i=1; i<size-1; i++) {
    /* print each column position... */
    for (j=1; j<size-1; j++)
      printf("%c", board[i*size + j] ? 'x' : ' ');
    
    /* followed by a carriage return */
    printf ("\n");
  }
}

/* read a file into the life board */
void read_file (FILE* f, cell_t* board, int size) {
  int   i, j;
  char* s = (char*) malloc(size+10);

  /* read the first new line (it will be ignored) */
  fgets (s, size+10,f);

  j = 0;
  for (i = 0; i < size; i++)
    board[i*size] = 0;

  j = size-1;
  for (i = 0; i < size; i++)
    board[i*size] = 0;

  i = 0;
  for (j = 0; j < size; j++)
    board[j] = 0;

  i = size*(size-1);
  for (j = 0; j < size; j++)
    board[i+j] = 0;

  /* read the life board */
  for (i=1; i<size-1; i++) {
    /* get a string */
    fgets (s, size+10,f);
    /* copy the string to the life board */
    for (j=1; j<size-1; j++)
      board[i*size + j] = (s[j-1] == 'x');
  }
}

int main () {
  FILE *f;
  f = stdin;
  fscanf(f,"%d %d", &size, &steps);
  cell_t* prev = allocate_board (size+2);
  read_file (f, prev, size+2);
  fclose(f);
  cell_t* next = allocate_board (size+2);
  cell_t* tmp;
  int i;
  #ifdef DEBUG
    printf("Initial:\n");
    print(prev,size+2);
  #endif

  for (i=0; i<steps; i++) {
    play (prev,next,size+2);
    #ifdef DEBUG
      printf("%d ----------\n", i + 1);
      print (next,size+2);
    #endif
    tmp = next;
    next = prev;
    prev = tmp;
  }

#ifdef RESULT
  printf("Final:\n");
  print (prev,size+2);
#endif

  free_board(prev);
  free_board(next);
}
