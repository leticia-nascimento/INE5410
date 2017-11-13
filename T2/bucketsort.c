#include <stdio.h>
 
#define bucketSize 100
//#define nBuckets 10
#define max 10
 
typedef struct {
        int top;
        int bucket[bucketSize];
} bucket;
 
void bucket_sort(int v[],int tam);
void bubble(int v[],int tam);                                                 
                                                                  
void bucket_sort(int v[],int tam){                                     
        bucket b[nBuckets];                                      
        int i,j,k;  

        for(i = 0; i < nBuckets; i++) {
                b[i].top = 0;
        }
         
        for(i = 0; i < tam; i++) {
                j = (nBuckets)-1;
                while(1) {
                        if(j < 0)
                                break;
                        if(v[i]>=j*10) {
                                b[j].bucket[b[j].top]=v[i];
                                (b[j].top)++;
                                break;
                        }
                        j--;
                }
        }
         
        for(i = 0;i < nBuckets; i++){
                if(b[i].top)
                        bubble(b[i].bucket,b[i].top);
        }
         
        i = 0;
        for(j = 0; j < nBuckets; j++){
                for(k = 0; k < b[j].top; k++){
                        v[i] = b[j].bucket[k];
                        i++;
                }
         }
 }
 
void bubble(int v[],int tam){
        int i,j,temp,flag;
        if(tam)
                for(j = 0; j < tam-1; j++){
                        flag = 0;
                        for(i = 0; i < tam-1; i++){
                                 if(v[i+1] < v[i]){
                                         temp = v[i];
                                         v[i] = v[i+1];
                                         v[i+1] = temp;
                                         flag=1;
                                 }
                        }
                        if(!flag)
                                 break;
                }
 }

int main(int argc, char* argv[]) {
        int size = atoi(argv[1]); // tamanho do vetor
        int nbuckets = atoi(argv[2]); // quantidade de buckets
        int nprocs; // quantidade de processos

        //int tam = 10;
        //int vetor[10] = {1, 5, 2, 45, 6, 6, 23, 0, 24, 31};
        int vet[size]; // vetor principal

        srand((unsigned)time(NULL)); // inicializa random

        // inicializar o vetor
        printf("Before sorting:\n");
        for(int i = 0; i < size; i++) {
                vet[i] = (rand() % 50); // random de no maximo 20
                printf("%d ",vet[i]);
        }

        bucket_sort(vet, size, nbuckets);

        for(int i = 0; i < size; i++) {
                printf("%d ", vetor[i]);
        }
        printf("\n");
}