#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv){

int rank, size, ierr;
int sendto, recvfrom;
int ourtag = 24;
char sendmessage[] = "Hello";
char getmessage[6];
int i=0,k,j;
MPI_Status rstatus;

ierr = MPI_Init(&argc,&argv);
ierr = MPI_Comm_size(MPI_COMM_WORLD, &size);
ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank);

if(rank == 0){
	//Comecando o envio das messagens
	//Enviando messagem de 0 -> 1
	sendto = 1;
	ierr = MPI_Ssend(sendmessage, 6, MPI_CHAR, sendto, ourtag, MPI_COMM_WORLD);
	printf("Messagem enviada de %d -> %d com a TAG : %d\n",rank, sendto, ourtag);
}else{	
	if(rank != (size-1)){
	//Realiza a verificacao de onde esta vinda a msg 
	ierr = MPI_Recv(getmessage, 6, MPI_CHAR, rank-1, ourtag, MPI_COMM_WORLD, &rstatus);
	//Mensagem recebida pelo processador de rank
	printf("Mensagem recebida de %d -> %d com a TAG : %d\n",rank-1, rank,ourtag);
	ierr = MPI_Ssend(sendmessage, 6, MPI_CHAR, rank+1, ourtag, MPI_COMM_WORLD);
        printf("Messagem enviada de %d -> %d com a TAG : %d\n",rank, rank+1, ourtag);
	}else{	
		ierr = MPI_Recv(getmessage, 6, MPI_CHAR, rank-1, ourtag, MPI_COMM_WORLD, &rstatus);
		printf("Mensagem Chegou ao rank 7");
	}
}
MPI_Finalize();
return 0;
}
