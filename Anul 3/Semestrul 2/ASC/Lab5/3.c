#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

// alocare in zona continua de memorie
double **alloc(int w, int h)
{
    double **mat;
    double *buf;
    buf = (double *) calloc(h * w, sizeof(double));
    int i;
    mat = (double **) calloc(h, sizeof(double *));
    for (i = 0; i < h; i++)
        mat[i] = buf + i * w;
    return mat;
}

int main(int argc, char** argv){

	struct timeval start,finish;
	double t;
	double **a,**b,**c;
	int i,j,k,N,m,n,o;
	N = 8;
	a = alloc(N,N);
	b = alloc(N,N);
	c = alloc(N,N);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			a[i][j] = rand() % 2;
			b[i][j] = rand() % 2;
			c[i][j] = 0;
		}
	}




	gettimeofday(&start,0);

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			c[i][j] = 0.0;
			for (k = 0; k < N; k++){
				c[i][j] += a[i][k] * b[k][j];
			}
		}
	}

	gettimeofday(&finish,0);

	t = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec) / 1000000.0;
	printf("Baza = %lf\n", t);


	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%lf ",c[i][j]);
		}
		printf("\n");
	}

	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j]=0;



	gettimeofday(&start,0);




	int z=4;
	
	for (i = 0; i < N; i+=N/z){
		for (j = 0; j < N; j+=N/z){
			for (k = 0; k < N; k+=N/z){

				for (m = i; m < i + N/z; m++){
					for (n = j; n < j + N/z; n++){
						for (o = k; o < k + N/z; o++){
							
							c[m][n] += a[m][o] * b[o][n];
						}
					}
				}
			}
		}
	}
	
	gettimeofday(&finish,0);

	t = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec) / 1000000.0;
	printf("OPTIMIZARE  = %lf\n", t);

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			printf("%lf ",c[i][j]);
		}
		printf("\n");
	}




	return 0;
}