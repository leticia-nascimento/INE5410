#include <stdio.h>
#include <math.h>

void bucket_sort(int* v, int size, int nbuckets, float range);
void quick_sort(int* v,int size);
int maxValue(int* v, int size);                                                
int minValue(int* v, int size);
void initialize(int* v, int size);
void print(int* v, int size);
int** allocate_bucket(int nbuckets, int size);
int* allocate_vector(int size);                                           

// separa o vetor em buckets, e chama o bubble_sort para ordenar separadamente cada bucket
void bucket_sort(int* v, int size, int nbuckets, float range) {
    int** bucket = allocate_bucket(nbuckets, size);

    int i,j,k,b;

    // garantir que todos os buckets estejam vazios
    for(i = 0; i < nbuckets; i++) {
        for(j = 0; j < size; j++) {
            bucket[i][j] = 0;
        }
    }

    printf("\n");
    for(b = 0; b < nbuckets; b++) {
        printf("Bucket: %d\n", b);
        for(i = 0; i < size; i ++) {
            printf("Numbers in this bucket: ");
            int number = v[i];
            float index = floor((v[i]-minValue(v, size)) / range);
            printf("%.1lf\n", index);
            bucket[b][(int)index] = number;
            printf("%d\n", bucket[b][(int)index] = number);
        }
        printf("\n");
    }

    // for(i = 0; i < nbuckets; i++) {
    //     for(j = 0; j < size; j++) {
    //         if(v[])
    //         int* b = allocate_vector();
    //     }
    // }

    // for(i = 0; i < size; i++) {
    //     quick_sort(bucket[i][], size);
    // }
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
        v[i]     = v[j];
        v[j]     = temp;
      }
     
      quick_sort(v, i);
      quick_sort(v + i, size - i);
}

// encontrar o maior valor de um vetor
maxValue(int* v, int size) {
    int max = v[0];

    for (int i = 1; i < size; ++i) {
        if (v[i] > max ) {
            max = v[i];
        }
    }
    return max;
}

// encontrar o menor valor de um vetor
minValue(int* v, int size) {
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

//aloca memória para um bucket com um vetor de elementos
int** allocate_bucket(int nbuckets, int size) {
    int ** bucket = (int **) malloc(sizeof(int*)*nbuckets);
    int i;
    for (i = 0; i < size; i++)
        bucket[i] = (int *) malloc(sizeof(int)*size);
    return bucket;
}

int main(int argc, char* argv[]) {
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

        //bubble(v, size);
        bucket_sort(v, size, nbuckets, range);

        printf("\nAfter sorting:\n");
        print(v, size);
}

