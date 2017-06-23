/**
	Exercício 1 Faça um programa usando MPI que implemente o padrão mestre/escravo.
	Inicialmente, o processo mestre deverá enviar uma mensagem
	para cada um dos escravos. Ao receberem a mensagem, os processos escravos
	deverão respondê-la, enviando uma mensagem com o seu rank. Ao
	receber uma mensagem de um processo escravo, o processo mestre deverá
	imprimir o rank do processo escravo.
*/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
	int size, rank;
	int flag = 0;

	MPI_Init(&argc,	&argv); //	inicializa o ambiente MPI
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);

	if (rank == 0) {
		for (int i = 1; i < size; i++) {
			MPI_Send(NULL, 0, MPI_INT, i, 0, MPI_COMM_WORLD);
		}
		while (flag < size-1) {
			MPI_Recv(&rank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("Message received from process %d\n", rank);
			flag++;
		}
		rank = 0;
	} else {
		MPI_Recv(NULL, 0, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
		MPI_Send(&rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

	MPI_Barrier(MPI_COMM_WORLD);
	MPI_Finalize();	// finaliza o ambiente MPI

	return	0;
}