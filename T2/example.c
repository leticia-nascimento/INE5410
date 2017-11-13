#include <stdio.h>
 
 #define tam_bucket 100
 
 typedef struct {
         int topo;
         int balde[tam_bucket];
 }bucket;
 
 void bucket_sort(int v[],int tam, int num_bucket);                   //cabeçalho das funções
 void bubble(int v[],int tam);                                                 
                                                                  
 void bucket_sort(int v[],int tam, int num_bucket){                                     
         bucket b[num_bucket];                                      
         int i,j,k;                                                 
 /* 1 */ for(i=0;i<num_bucket;i++)                    //inicializa todos os "topo"
                 b[i].topo=0;
         
 /* 2 */ for(i=0;i<tam;i++){                          //verifica em que balde o elemento deve ficar
                 j=(num_bucket)-1;
                 while(1){
                         if(j<0)
                                 break;
                         if(v[i]>=j*10){
                                 b[j].balde[b[j].topo]=v[i];
                                 (b[j].topo)++;
                                 break;
                         }
                         j--;
                 }
         }
         
 /* 3 */ for(i=0;i<num_bucket;i++)                     //ordena os baldes
                 if(b[i].topo)
                         bubble(b[i].balde,b[i].topo);
         
         i=0;
 /* 4 */ for(j=0;j<num_bucket;j++){                    //põe os elementos dos baldes de volta no vetor
                 for(k=0;k<b[j].topo;k++){
                         v[i]=b[j].balde[k];
                         i++;
                 }
         }
 }
 
 void bubble(int v[],int tam){
         int i,j,temp,flag;
         if(tam)
                 for(j=0;j<tam-1;j++){
                         flag=0;
                         for(i=0;i<tam-1;i++){
                                 if(v[i+1]<v[i]){
                                         temp=v[i];
                                         v[i]=v[i+1];
                                         v[i+1]=temp;
                                         flag=1;
                                 }
                         }
                         if(!flag)
                                 break;
                 }
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

        bucket_sort(v, size, nbuckets);

        printf("\nAfter sorting:\n");
        print(v, size);
}