#include <stdio.h>
#include <math.h>

typedef struct {
    int index;
    int size;
    int *elements;
} bucket;
 
void bucket_sort(int v[],int size, int nbuckets, float range);
void quicksort(int v[],int size);
int maxValue(int v[], int size);                                                
int minValue(int v[], int size);                                                
                                                                  
void bucket_sort(int v[], int size, int nbuckets, float range) {
    int **buckets;
    //bucket b[nbuckets];
    int r = (int) range;            
        
    int i,j,k, e;  

    for(i = 0; i < nbuckets; i++) {
        b[i].index = i;
        b[i].size = r;
        for (e = 0; e < 5; e++)
            b[i].elements[e] = 1;
            //printf("%d\n", b[i].elements[e]);
        //printf("%d\n", b[i].index);
        //printf("%d\n", b[i].size);
    }
         
    // for(i = 0; i < size; i++) {
    //     j = (nbuckets-1);
    //     while(1) {
    //         if(j < 0)
    //             break;
    //         if(v[i] >= j*range) {
    //             b[j].bucket[b[j].top] = v[i];
    //             (b[j].top)++;
    //             break;
    //         }
    //         j--;
    //     }
    // }
         
    // for(i = 0;i < nbuckets; i++){
    //     quicksort(b[i].elements[i],b[i].size);
    // }
         
    // i = 0;
    // for(j = 0; j < nbuckets; j++){
    //     for(k = 0; k < b[j].top; k++){
    //         v[i] = b[j].bucket[k];
    //         i++;
    //     }
    // }
 }

void quicksort(int v[], int size) {
  if (size < 2) return;
 
  int pivot = v[size/2];
 
  int i, j;
  for (i = 0, j = size - 1; ; i++, j--) {
    while (v[i] < pivot) i++;
    while (v[j] > pivot) j--;
 
    if (i >= j) break;
 
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
  }
 
  quicksort(v, i);
  quicksort(v + i, size - i);
}

// encontrar o maior valor de um vetor
maxValue(int v[], int size) {
    int max = v[0];

    for (int i = 1; i < size; ++i) {
        if (v[i] > max ) {
            max = v[i];
        }
    }
    return max;
}

// encontrar o menor valor de um vetor
minValue(int v[], int size) {
    int min = v[0];

    for (int i = 1; i < size; ++i) {
        if (v[i] < min ) {
            min = v[i];
        }
    }
    return min;
}

// inicializa vetor
void initialize(int v[], int size) {
    for(int i = 0; i < size; i++) {
        v[i] = (rand() % 30); // random de no maximo 30
    }
}

// printa vetor
void print(int v[], int size) {
    for(int i = 0; i < size; i++) {
        printf("%d ",v[i]);
    }
    printf("\n");
}


int main(int argc, char* argv[]) {
        int size = atoi(argv[1]); // tamanho do vetor
        printf("Size: %d\n", size);
        int nbuckets = atoi(argv[2]); // quantidade de buckets
        printf("Number of buckets: %d\n", nbuckets);
        int nprocs; // quantidade de processos

        int v[size]; // vetor principal

        srand((unsigned)time(NULL)); // inicializa random

        printf("\nBefore sorting:\n");
        initialize(v, size);
        print(v, size);

        int max = maxValue(v, size);
        int min = minValue(v, size);
        printf("\nMax number: %d\n", max);
        printf("Min number: %d\n", min);

        float range = floor((max - min) / nbuckets)+1;    
        printf("Range: %.1lf\n", range);
        printf("\n");

        bucket_sort(v, size, nbuckets, range);

        printf("\nAfter sorting:\n");
        print(v, size);
}

