#include <stdio.h>
#include <math.h>
#include <mpi.h>
#include <stdlib.h>
 
#define bucketsize 100

typedef struct {
        int top;
        int* elements;
} bucket;
 
void bucket_sort(int* v, int size, int nbuckets, float range);
void quick_sort(int* v, int size);
int maxValue(int* v, int size);                                                
int minValue(int* v, int size);
void initialize(int* v, int size);
void print(int* v, int size);
int* allocate_vector(int size);                                                      

void allocate_buckets(bucket* bucket, int nbuckets) {
    bucket->elements = malloc(sizeof(int)*nbuckets);
    bucket->top = 0;
}

void insert(bucket* bucket, int* data) {
    bucket->elements[bucket->top++] = *data;
}

void bucket_sort(int v[],int size, int nbuckets, float range){                                     
    bucket *buckets[nbuckets];

    int i,j,k;

    for(i = 0; i < nbuckets; i++) 
        allocate_buckets(&buckets[i], size);
    }

      
    for (i = 0; i < size; ++i) {
        j = (nbuckets)-1;
        while(1) {
                if(j < 0) break;
                if(v[i]>=j*range){
                        b[j].bucket[b[j].top]=v[i];
                        (b[j].top)++;
                        break;
                        }
                        j--;
                }
        }

    for (i = 0; i < nbuckets; i++) {
        if(b[i].top)
                quick_sort(b[i].bucket,b[i].top);
     }

    i = 0;
    for (j = 0; j < nbuckets; +j++) {        
        for(k = 0; k < b[j].top; k++){
                v[i]=b[j].bucket[k];
                i++;
        }
    }
}

//quick sort para ordenar o vetor                                                              
void quick_sort(int *v, int size) {
    if (size < 2) return;
     
    int pivot = v[size / 2];
     
    int i, j;
    for (i = 0, j = size - 1; ; i++, j--) {
        while (v[i] < pivot) i++;
        while (v[j] > pivot) j--;
     
        if (i >= j) break;
     
        int temp = v[i];
        v[i] = v[j];
        v[j] = temp;
      }
     
      quick_sort(v, i);
      quick_sort(v + i, size - i);
}

// encontrar o maior valor de um vetor
int maxValue(int* v, int size) {
    int max = v[0];

    for (int i = 1; i < size; ++i) {
        if (v[i] > max ) {
            max = v[i];
        }
    }
    return max;
}

// encontrar o menor valor de um vetor
int minValue(int* v, int size) {
    int min = v[0];

    for (int i = 1; i < size; ++i) {
        if (v[i] < min ) {
            min = v[i];
        }
    }
    return min;
}

// inicializa vetor
void initialize(int* v, int size) {
    for(int i = 0; i < size; i++) {
        v[i] = (rand() % 50); // random de no maximo 30
    }
}

// printa vetor
void print(int* v, int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ", v[i]);
    }
    printf("\n");
}

// aloca memória para um vetor linear
int* allocate_vector(int size) {
    int * vector = (int *) malloc(sizeof(int)*size);
    int i;
    for (i = 0; i < size; i++)
        vector[i] = (int *) malloc(sizeof(int)*size);
    return vector;
}

int main(int argc, char* argv[]) {
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

void MasterWork() {
    int size = atoi(argv[1]); // tamanho do vetor
    printf("Size: %d\n", size);
    int nbuckets = atoi(argv[2]); // quantidade de buckets
    printf("Number of buckets: %d\n", nbuckets);
    int nprocs; // quantidade de processos

    int *v = allocate_vector(size);

    srand((unsigned)time(NULL)); // inicializa random

    printf("\nBefore sorting:\n");
    initialize(v, size);
    print(v, size);

    printf("\nMax number: %d\n", maxValue(v, size));
    printf("Min number: %d\n", minValue(v, size));

    float range = floor((maxValue(v, size) - minValue(v, size)) / nbuckets)+1;    
    printf("Range: %.1lf\n", range);

    bucket_sort(v, size, nbuckets, range);

    printf("\nAfter sorting:\n");
    print(v, size);

    return 0;
}