#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

int main(){

int i;
double pi,x,y, count = 0.0, npoint = 10000;
srand(time(NULL));

for( i = 1; i < npoint; i++){
	x = (double)rand()/(double)RAND_MAX;
	y = (double)rand()/(double)RAND_MAX;
	if( (x*x + y*y) < 1){ 
		count++;
	}
	printf("X : %lf \t Y : %lf\n", x,y);
}

printf("PI : %lf\n", 4.0*count/npoint);
return 0;
}
