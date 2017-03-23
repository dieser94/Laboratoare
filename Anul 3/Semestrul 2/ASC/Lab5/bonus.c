#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>

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
	int i,j,k,N,m,n,o,z;
	N = 1000;
	a = alloc(N,N);
	b = alloc(N,N);
	c = alloc(N,N);

	printf("1\n");

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

	printf("2\n");

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
	printf("Timp CAZ i-j-k = %lf\n", t);









	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j]=0;




	gettimeofday(&start,0);

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			c[i][j] = 0.0;
			for (k = 0; k < N; k++){
				c[i][k] += a[i][j] * b[k][j];
			}
		}
	}

	gettimeofday(&finish,0);

	t = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec) / 1000000.0;
	printf("Timp CAZ i-k-j = %lf\n", t);












	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j]=0;



	gettimeofday(&start,0);

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			c[i][j] = 0.0;
			for (k = 0; k < N; k++){
				c[k][j] += a[k][k] * b[i][j];
			}
		}
	}

	gettimeofday(&finish,0);

	t = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec) / 1000000.0;
	printf("Timp CAZ j-k-i = %lf\n", t);


	printf("3\n");
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



	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j]=0;



	gettimeofday(&start,0);




	z=4;
	
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

	free(a);
	free(b);
	free(c);

	printf("~==============NORMAL ALLOC STARTING =============~\n");

	a = (double**) malloc (1000 * sizeof(double*));
	b = (double**) malloc (1000 * sizeof(double*));
	c = (double**) malloc (1000 * sizeof(double*));

	for (i = 0; i < N; i++) {
		a[i] = (double*) calloc(1000 , sizeof(double));
		b[i] = (double*) calloc(1000 , sizeof(double));
		c[i] = (double*) calloc(1000 , sizeof(double));
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



	printf("2 \n");
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
	printf("Timp CAZ i-j-k = %lf\n", t);









	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j]=0;




	gettimeofday(&start,0);

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			c[i][j] = 0.0;
			for (k = 0; k < N; k++){
				c[i][k] += a[i][j] * b[k][j];
			}
		}
	}

	gettimeofday(&finish,0);

	t = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec) / 1000000.0;
	printf("Timp CAZ i-k-j = %lf\n", t);












	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j]=0;



	gettimeofday(&start,0);

	for (i = 0; i < N; i++){
		for (j = 0; j < N; j++){
			c[i][j] = 0.0;
			for (k = 0; k < N; k++){
				c[k][j] += a[k][k] * b[i][j];
			}
		}
	}

	gettimeofday(&finish,0);

	t = (finish.tv_sec - start.tv_sec) + (double)(finish.tv_usec - start.tv_usec) / 1000000.0;
	printf("Timp CAZ j-k-i = %lf\n", t);


	printf("3 \n");

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



	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			c[i][j]=0;



	gettimeofday(&start,0);




	z=4;
	
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








	return 0;
}
