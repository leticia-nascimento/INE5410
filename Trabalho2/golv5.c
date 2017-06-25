// Version 4: include mpi
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
#include <mpi.h>

#define DOGGO 1000

typedef unsigned char cell_t;

int size, steps;
int nprocs, rank;

enum mpitags {
  MT_SETTING,
  MT_INITIAL,
  MT_RESULT,
  MT_FINISH
};

cell_t* allocate_board (int size) {
  size = size+2;
  cell_t* board = (cell_t*) malloc(sizeof(cell_t*)*size*size);
  return board;
}

void free_board (cell_t* board) {
  free(board);
}

/* return the number of on cells adjacent to the i,j cell */
int adjacent_to (cell_t* board, int size, int i, int j) {
  int count = 0;

  int sk = (i-1)*size;
  int ek = (i+1)*size;
  int sl = j-1;
  int el = j+1;

  count=board[sk + sl];
  count+=board[sk + j];
  count+=board[sk + el];
  count+=board[i*size + sl];
  count+=board[i*size + el];
  count+=board[ek + sl];
  count+=board[ek + j];
  count+=board[ek + el];
  
  if (rank == DOGGO) {
    if (count != 0) {
      printf("r%d size%d i%d j%d\n", rank, size, i, j);
      printf("sk%d ek%d sl%d el%d\n", sk, ek, sl, el);
      printf("count%d\n", count);
    }
  }

  return count;
}

void play (cell_t* board, cell_t* newboard, int size, int rows) {
  int   i, j, a;
  /* for each cell, apply the rules of Life */
  for (i=1; i<rows-1; i++) {
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
  size = size + 2;
  /* for each row */
  for (i=1; i<size-1; i++) {
    /* print each column position... */
    for (j=1; j<size-1; j++)
      printf("%c", board[i*size + j] ? 'x' : ' ');
    
    /* followed by a carriage return */
    printf ("\n");
  }
}

/* print non quad board */
void printpart (cell_t* board, int size, int rows, int s, char p) {
  printf("r%d %d %c ----------\n", rank, s, (p?'p':'n') );
  int   i, j;
  /* for each row */
  for (i=0; i<rows; i++) {
    /* print each column position... */
    for (j=0; j<size; j++)
      printf("%c", board[i*size + j] ? 'x' : ' ');
    
    /* followed by a carriage return */
    printf ("\n");
  }
}

/* read a file into the life board */
void read_file (FILE* f, cell_t* board, int size) {
  int   i, j;
  size = size + 2;
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

void MasterWork() {
  FILE *f;
  f = stdin;
  fscanf(f,"%d %d", &size, &steps);
  int newsize = size+2;
  int nslaves = nprocs-1;

  cell_t* prev = allocate_board (size);
  read_file (f, prev, size);
  fclose(f);
  cell_t* next = allocate_board (size);
  cell_t* tmp;

  int i;
  #ifdef DEBUG
    printf("Initial:\n");
    print(prev,size);
  #endif

  // Envia as variáveis de inicialização pros processos
  int msg[2];
  msg[0] = size;
  msg[1] = steps;
  //printf("r: %d size: %d steps: %d\n", rank, msg[0], msg[1]);

  for (i=1; i<nprocs; i++) {
    MPI_Send(msg, 2, MPI_INT, i, MT_SETTING, MPI_COMM_WORLD);
  }
  //printf("r%d enviou settings.\n", rank);

  int id, start;
  int linesPerProc = newsize/nslaves;
  int linesLast = linesPerProc + (newsize%nslaves);

  // Calcula a quantidade de celulas pra cada processo
  int quant1s = (linesPerProc+1)*newsize;
  int quant2s = (linesPerProc+2)*newsize;
  int quant3s = (linesLast+1)*newsize;
  int quant1r = (linesPerProc-1)*newsize;
  int quant2r = (linesPerProc)*newsize;
  int quant3r = (linesLast-1)*newsize;

  //printf("q1s %d q2s %d q3s %d q1r %d q2r %d q3r %d \n", quant1s, quant2s, quant3s, quant1r, quant2r, quant3r );

  for (i=0; i<steps; i++) {
    /*** Envia para cada escravo calcular seu step ***/

    // Primeiro escravo
    id = 1;
    //printf("master Send. id %d start %d end %d\n", id, start, (quant1s-1));
    MPI_Send(prev, quant1s, MPI_CHAR, id, MT_INITIAL, MPI_COMM_WORLD);
    //printf("master passou Send.\n");    

    // Escravos intermediários
    for (id=2; id<nslaves; id++) {
      start = newsize*linesPerProc*(id-1)-newsize;
      //printf("master Send. id %d start %d end %d\n", id, start, (start+quant2s-1));
      MPI_Send((prev+start), quant2s, MPI_CHAR, id, MT_INITIAL, MPI_COMM_WORLD);
    }
    //printf("master passou for.\n");

    // Ultimo escravo
    start = newsize*linesPerProc*(id-1)-newsize;
    //printf("master Send. id %d start %d end %d\n", id, start, (start+quant3s-1));
    MPI_Send((prev+start), quant3s, MPI_CHAR, id, MT_INITIAL, MPI_COMM_WORLD);
    //printf("master passou ultimo Send.\n");

    /*** Recebe os resultados de cada escravo ***/

    // Primeiro escravo
    id = 1;
    start = newsize;
    MPI_Recv((next+start), quant1r, MPI_CHAR, id, MT_RESULT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Escravos intermediários
    for (id=2; id<nslaves; id++) {
      start = newsize*linesPerProc*(id-1);
      MPI_Recv((next+start), quant2r, MPI_CHAR, id, MT_RESULT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }

    // Ultimo escravo
    start = newsize*linesPerProc*(id-1);
    MPI_Recv((next+start), quant3r, MPI_CHAR, id, MT_RESULT, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Apos receber todos, imprime e faz swap dos ponteiros
    #ifdef DEBUG
      printf("%d ----------\n", i + 1);
      print (next,size);
    #endif
    tmp = next;
    next = prev;
    prev = tmp;

    // Avisa todos os processos para terminarem
    if (i == (steps-1)) {
      for (id = 1; id < nprocs; id++) {
        MPI_Send(NULL, 0, MPI_INT, id, MT_FINISH, MPI_COMM_WORLD);
        //printf("master sent MT_FINISH id %d\n", id);
      }
    }
  }

  #ifdef RESULT
    printf("Final:\n");
    print (prev,size);
  #endif

  free_board(prev);
  free_board(next);
}

void SlaveWork() {
  int msg[2] = {-1, -1};
  MPI_Recv(msg, 2, MPI_INT, 0, MT_SETTING, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
  size = msg[0];
  steps = msg[1];
  //printf("r%d size: %d steps: %d\n", rank, size, steps);

  int myId = rank - 1;
  int newsize = size+2;
  int nslaves = nprocs-1;
  int linesPerProc = newsize/nslaves;
  int quant = 0;

  //printf("r%d antes do if.\n", rank);
  if (myId == 0) { // Primeiro escravo
    quant = (linesPerProc+1)*newsize;
  } else if (myId < nslaves-1) { // Demais escravos
    quant = (linesPerProc+2)*newsize;
  } else { // Ultimo escravo
    linesPerProc += (newsize%nslaves);
    quant = (linesPerProc+1)*newsize;
  }
  //printf("r%d quant: %d\n", rank, quant);

  cell_t* prev = (cell_t*) malloc(sizeof(cell_t*)*quant);
  cell_t* next = (cell_t*) malloc(sizeof(cell_t*)*quant);

  //printf("r%d depois do malloc.\n", rank);

  int i;
  for (i=0; i<steps; i++) {
    //printf("r%d entrou no loop.\n", rank);

    // Recebe sua parte do tabuleiro
    MPI_Recv(prev, quant, MPI_CHAR, 0, MT_INITIAL, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    //printf("r%d passou Recv.\n", rank);
    // Calcula a iteração
    if (rank == DOGGO) {
      printpart(prev,newsize, (quant/newsize), i+1, 1 );
    }
    play(prev, next, newsize, (quant/newsize) );
    if (rank == DOGGO) {
      printpart(next,newsize, (quant/newsize), i+1, 0 );
    }
    // Envia apenas as linhas válidas (sem a primeira e a ultima)
    MPI_Send((next+newsize), (quant-newsize*2), MPI_CHAR, 0, MT_RESULT, MPI_COMM_WORLD);
    //printf("r%d passou Send.\n", rank);
  }

  free(prev);
  free(next);
}

int main (int argc, char* argv[]) {
  MPI_Init(&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  if (rank == 0) { // Mestre
    MasterWork();
  } else {
    SlaveWork();
  }

  MPI_Finalize();
  return 0;
}
