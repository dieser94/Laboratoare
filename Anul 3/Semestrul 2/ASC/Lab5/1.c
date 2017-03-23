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
	int i,j,k,N;
	N = 1000;
	a = alloc(1000,1000);
	b = alloc(1000,1000);
	c = alloc(1000,1000);

	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			a[i][j] = rand() % 100;
			b[i][j] = rand() % 100;
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









	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j]=0;


	gettimeofday(&start,0);

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			register double suma = 0.0;
			for (k = 0; k < N; k++){
				suma += a[i][k] * b[k][j];
			}
			c[i][j] = suma;
		}
	}

	gettimeofday(&finish,0);

	t = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec) / 1000000.0;
	printf("OPTIMIZARE CONSTANTE = %lf\n", t);









	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j]=0;


	gettimeofday(&start,0);

	for (i = 0; i < N; i++){
		double *orig_pa = &a[i][0];
		for (j = 0; j < N; j++){
			double *pa = orig_pa;
			double *pb = &b[0][j];
			register double suma = 0;
			for (k = 0; k < N; k++){
				suma += *pa * *pb;
				pa++;
				pb += N;
			}
			c[i][j] = suma;
		}
	}

	gettimeofday(&finish,0);

	t = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec) / 1000000.0;
	printf("OPTIMIZARE ACCES LA VECTORI = %lf\n", t);




	return 0;
}
