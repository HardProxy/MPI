#include<stdio.h>
#include<mpi.h>
#include<malloc.h>

void show_m(double *mat, int N){
	int i, j;

	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
			printf("%lf\t", mat[i*N + j]);
		}
		printf("\n");
	}
}

int main(int argc, char **argv){

	int rank, size, ierr, N = 5, i,j;
	MPI_Status status;
	
	//Alocacao de memoria 
	double *m_vet,*a, *div, soma = 0, *result;
	
	//Matriz 5X5 Vetorizada
	m_vet = malloc(N*N*sizeof(double));
	a = malloc(N*sizeof(double));

	//Atribuicao de valores sinteticos
	for(i = 0; i < N; i++){
		for(j = 0; j < N; j++){
		m_vet[i*N + j] = j+1; 
		}
		a[i] = i+1;
	}
	
	//show_m(m_vet, N);
	
	//Inicializando MPI
	ierr = MPI_Init(&argc,&argv);
	//Informacoes sobre processadores
	ierr = MPI_Comm_size(MPI_COMM_WORLD,&size);
	ierr = MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	
	printf("Processador : %d \n",rank);
	
	div = malloc(N*sizeof(double));
	// Scatter
	MPI_Scatter(m_vet, N, MPI_DOUBLE, div, N, MPI_DOUBLE,0,MPI_COMM_WORLD );		
	
	for(i = 0; i < N; i++)
		soma += div[i]*a[i];	
	printf("Resultado col %d : %lf\n", rank,soma);

	if(rank == 0){
		result = malloc(N*sizeof(double))	;
	}
	
	MPI_Gather(&soma, 1,MPI_DOUBLE, result,1,MPI_DOUBLE,0,MPI_COMM_WORLD);			
	if(rank == 0){
		printf("Vetor resultante : \n");
		for(i = 0; i < N; i++)
			printf("%lf\n",result[i]);
	}

	MPI_Finalize();
return 0;

}
