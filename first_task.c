#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int* multiply_vector(int* vector_a, int* vector_b, int* vector_sum, int size) {
    int i;
    for(i = 0; i < size; i++) {
        vector_sum[i] = vector_a[i] * vector_b[i];
    }
    return vector_sum;
}

int main(int argc, char **argv) {
    time_t t;
    srand((unsigned) time(&t));

    int size = atoi(argv[1]);
    int* vector_a = malloc(size*sizeof(int));
    int* vector_b = malloc(size*sizeof(int));
    int* vector_sum = malloc(size*sizeof(int));

    int i;
    for(i = 0; i < size; i ++) {
        vector_a[i] = (rand() % 1000);
        vector_b[i] = (rand() % 1000);
    }

    multiply_vector(vector_a, vector_b, vector_sum, size);

    for(i = 0; i < size; i++) {
        printf("%d ", vector_sum[i]);
    }

    printf("\n");
}
