#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<mpi.h>
int main(int argc, char **argv){

//Variaveis compartilhadas
int rank, size, ierr, tag=24;
double count = 0.0, npoint = 300000;
MPI_Status rstatus;
//Alterando a semente pelo tempo 
srand(time(NULL));
//Inicializando MPI
ierr = MPI_Init(&argc,&argv);
//Buscando informacoes sobre os processadores 
ierr = MPI_Comm_size(MPI_COMM_WORLD, &size);
ierr = MPI_Comm_rank(MPI_COMM_WORLD, &rank);
// Variaveis de cada thread
double points,pcount, getcount,x,y,sendpoint=npoint/(size-1);
int i;
if ( rank == 0 ) {
	//Enviando para todas os outros processadores a quantidade
	//de pontos que vao gerar
	for ( i = 1; i < size; i++)
		MPI_Ssend(&sendpoint,1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD);
	//Recebendo os pontos dentro do circulo de cada processador
	for ( i = 1; i < size; i++){
		MPI_Recv(&getcount,1, MPI_DOUBLE, i, tag, MPI_COMM_WORLD, &rstatus);
		count += getcount;	
	}
	printf("PI : %lf\n", 4.0*count/npoint);
}else{
	//Recebendo a quantidade de pontos a serem geradas
	MPI_Recv(&points, 1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD, &rstatus);
	//Gerando os pontos aleatorios
	for( i = 1; i < points; i++){
		x = (double)rand()/(double)RAND_MAX;
		y = (double)rand()/(double)RAND_MAX;
		if( (x*x + y*y) < 1){ 
			pcount++;	
		}
	}
	//Enviando a quantidade pontos dentro do circulo 
	MPI_Ssend(&pcount,1, MPI_DOUBLE, 0, tag, MPI_COMM_WORLD);
}
ierr = MPI_Finalize();
return 0;
}
