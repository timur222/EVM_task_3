#include "Func.h"

double mach_eps();
double mach_eps()
{
	double eps = 1.0;

	while (1.0 + eps / 2.0 > 1.0)
	{
		eps /= 2.0;
	}
	return eps;
} // машинное эпсилон

int main(int argc, char* argv[])
{
	if(argc<5){
		printf("Incorrect input\n");
                return -1;
	}
	int n = atoi(argv[1]), m = atoi(argv[2]);
	double* MultInd;
	double start, end, ForNorm, eps=atof(argv[3]);
	double Norm=0.0, NormInf, Nevyaz=0.0;
	int k = atoi(argv[4]), prob, ans;

	if (n == 0 || n < m) {
		printf("Incorrect input\n");
		return -1;
	}

	if ((k < 0) || (k > 4)) {
		printf("Incorrect input\n");
		return -1;
	}
	if(mach_eps()>eps){
		printf("Incorrect input\n");
                return -1;
	}

	double* Matrix = (double*)malloc(n * n * (sizeof(double)));
	double* X = (double*)malloc(n * (sizeof(double)));

	if (Matrix == NULL || X== NULL)
	{
		printf("No memory allocated\n");
		free(Matrix);
		free(X);
		return -1;
	}
	if ((argc == 6) && (k == 0)) {		
		prob = Input(Matrix, argv[5], n, &Norm);
		if (prob == -1) {
			printf("File don't exist\n");
			free(Matrix);
			free(X);
			return -1;
		}
		if (prob == -2)
		{
			printf("Insufficient data \n");
			free(Matrix);
			free(X);
			return -1;
		}
	}

	if((argc!=6)&&(k==0))
	{
		printf("File don't exist\n");
		free(Matrix);
		free(X);
		return -1;
	}
	if(k>0){
		for(int i=0; i<n ; i++){
			ForNorm=0;
			for(int j=0; j<n; j++){
				Matrix[i*n+j]=generate(k, n, i, j);
				ForNorm+=abs(generate(k, n, i, j));
			}
			if(ForNorm>Norm){Norm=ForNorm;}
		}
	}
	for(int i=0; i<n; i++){Nevyaz+=Matrix[i*n+i];}
	//      }
	//}

	/*double* InvMatrix = (double*)malloc(n * n * (sizeof(double)));;

	if (InvMatrix == NULL)
	{
		printf("No memory allocated\n");
		free(Matrix);
		free(InvMatrix);
		return -1;
	}
	for (prob = 0; prob < n; prob++) { InvMatrix[prob * n + prob] = 1; }
	//инициализация и заполнение*/

	//решение
	printf("Matrix : \n");
	POut(Matrix, n, n, m);
	printf("\n");
	printf("%e \n \n", Norm);
	Norm = 1 / Norm;
	for (int i = 0; i < n; i++)
	{
		MultInd = Matrix + i * n;
		for (int j = 0; j < n; j++)
		{
			MultInd[j] = MultInd[j] * (Norm);
			if(fabs(MultInd[j])>NormInf){
				NormInf=fabs(MultInd[j]);
			}
		}
	}
	start = clock();
	ans = Gauss(Matrix, X, eps, Norm, n);
	end = clock();
	start = (double)(end - start) / CLOCKS_PER_SEC;
	printf("time; %f \n", start);
	if (ans == -2) {
		printf("Degenerate matrix");
		free(Matrix);
		free(X);
		return -1;
	}

	printf("Matrix : \n");
        POut(Matrix, n, n, m);
        printf("\n");

	printf("Sobstv : \n");
        POut(X, 1, n, m);
        printf("\n");
	
	for(int i=0; i<n; i++){Nevyaz-=X[i];}

	printf("Nevyaz: %e \n", Nevyaz);

	//printf("Inverse Matrix: \n");
	//POut(InvMatrix, m, n, m);

	/*if ((argc == 5) && (k == 0)) {
		prob = Input(Matrix, argv[4], n, &Norm);
		if (prob == -1) {
			printf("File not found\n");
			free(Matrix);
			return -1;
		}
		if (prob == -2)
		{
			printf("Insufficient data \n");
			free(Matrix);
			return -1;
		}
	}

	if(k>0){
                for(int i=0; i<n ; i++){
                	for(int j=0; j<n; j++){
                        	Matrix[i*n+j]=generate(k, n, i, j);
                	}
                }
        }*/


	//printf("Error norm : %e\n", NormSol(Matrix, InvMatrix, n));
	
	free(X);
	free(Matrix);
	return 0;
}
