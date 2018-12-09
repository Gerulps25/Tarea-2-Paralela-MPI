//Nombre: Geraldine Barrera

#include <iostream>
#include "mpi.h"
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <math.h>


using namespace std;

void Llenararreglo(int A[],int n)
{
    srand(time(NULL));
    cout<<"llenamos el arreglo con números aleatorios: "<<endl;
    for(int i=0; i<=n;i++)
    {
        //Genera números aleatorios hasta 200
        A[i]=rand()%200;
    }
}

void Promedio(int A[10000], int n, float&promedio,float& sumaprom)
{
        for(int i =0 ; i<n;i++)
        {
        cout<<"Numero "<<i<<" en el arreglo: "<<A[i]<<endl;
        sumaprom=sumaprom+A[i];
        promedio=sumaprom/n;
        }
    cout<<"El promedio de los numeros del arreglo es: "<<promedio<<endl;

}


void Varianza(int A[],int n, float& sumavar,float& varianza,float promedio)
{

    float numvar,numvar1,denvar;
    for(int i =0 ; i<n ;i++){
    numvar=A[i]-promedio;
    numvar1=numvar*numvar;
    sumavar=numvar1+sumavar;
    denvar=n-1;
    varianza=sumavar/denvar;
    }
    cout<<"La varianza es : "<<varianza<<endl;
}

void DesviacionEstandar(float&desviacion, float varianza)
{
     desviacion=sqrt(varianza);
     cout<<"La desviacion estandar es : "<<desviacion<<endl;
}



int main(int argc, char** argv)
{

    int n=10001;
    int A[n];
    float sumavar=0;
    float promedio;
    float sumaprom=0;
    float varianza;
    float desviacion;
    int size;
    int rank;

    MPI_Status estado;

    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);


    cout << "PROGRAMA NUMEROS ALEATORIOS EN ARREGLO" << endl;
     Llenararreglo(A,n);
     Promedio(A,n,promedio,sumaprom);
     Varianza(A,n,sumavar,varianza,promedio);
     DesviacionEstandar(desviacion,varianza);

     if (rank==0)
    {
       promedio=Promedio(10000, n,promedio,sumaprom);

			MPI_Recv(&varianza, 1, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &estado);
			MPI_Recv(&desviacion, 1, MPI_FLOAT, 2, 0, MPI_COMM_WORLD, &estado);
			cout<<"El promedio es: "<<promedio<<endl;
			cout<<"La varianza es: "<<varianza<<endl;
            cout<<"la desviacion estandar es : "<<desviacion<<endl;
     }

     if (rank==1)
    {
      varianza=Varianza(10000, n,sumavar,varianza,promedio);
      MPI_Send(&varianza, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
    }

    if (rank==2)
    {
      desviacion=DesviacionEstandar(desviacion, varianza);
      MPI_Send(&desviacion, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}


