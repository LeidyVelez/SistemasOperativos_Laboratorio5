#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <pthread.h>
#include <time.h>


/*Variables globales y protipos de funciones*/
#define MAX_THREADS     6 //DEBE MODIFICARSE PARA CAPTURARSE EN TIEMPO DE COMPILACIÓN!!!
#define MAX_CUENTAS 10 //TAMBIÉN HAY QUE MODIFICARLA!!!!
/*----------------------------------------------------------------------------------------*/
void *realizarTransferencia(void *p);
/*----------------------------------------------------------------------------------------*/
int i, rndCuenta, nroHilos, cantCorrer, nroCuentas, valorIni=0,nCuentas[1];
char *numeroHilos, *cantidadTiempoCorrer, *valorInicial, *numeroCuentas, *nombreArchivo;
char final[10];


/*----------------------------------------------------------------------------------------*/
 /* tipo de datos y tabla con los parametros*/
/*Esta tabla contendrá los identificadores de cada hilo, se pasarán por referencia*/
typedef struct
  {   
   int idThread; 
  } t_Threads;
t_Threads Threads[MAX_THREADS]; 
 
/*----------------------------------------------------------------------------------------*/

  /* tipo de datos y tabla con los parametros*/
/*Esta tabla contendrá los identificadores y monto de cada cuenta*/
typedef struct                    
  {   
   int idCuenta; 
   int monto;
   bool semaforo;
  } t_Cuentas;
t_Cuentas Cuentas[MAX_CUENTAS];

/*----------------------------------------------------------------------------------------*/


int main(int argc, char *argv[]){
        pthread_attr_t attr;
         pthread_attr_init (&attr);
	pthread_t h[10];
	/*Captura de parámetros*/
	numeroHilos= argv[1];
	cantidadTiempoCorrer=argv[2]; 
	numeroCuentas=argv[3];	
	valorInicial=argv[4];
	if((numeroHilos==NULL )	|| (cantidadTiempoCorrer==NULL ) || (numeroCuentas==NULL) ||(valorInicial==NULL)){
	printf("Ingrese los valores de los parámetros!!");
	return;
	}
	nroHilos=atoi(numeroHilos);
	cantCorrer= atoi(cantidadTiempoCorrer);
	nroCuentas=atoi(numeroCuentas);
	valorIni=atoi(valorInicial);
	if((nroHilos<=0)|| (cantCorrer<=0)|| (nroCuentas<=0) || (valorIni<=0)){printf("Ingrese valores de parámetros mayores que cero!!");return;}
	printf("Creando Cuentas...\n"); 
	for(i=0; i<=nroCuentas;i++){
		Cuentas[i].idCuenta=i; /*Guardo el identificador de la cuenta*/
		Cuentas[i].monto=valorIni; /*Guardo el valor inicial de cada cuenta*/
                Cuentas[i].semaforo=true; /*Guardo el semaforo de cada cuenta*/
	}
	printf("Creando threads...\n"); 
        //nCuentas[1]= nroCuentas;
	    for (i=0; i<nroHilos; i++) 
      		{  
			pthread_create(&h[i],NULL,realizarTransferencia,NULL);
		      } 
       for (i=0; i<nroHilos; i++) 
      		{ 
              pthread_join(h[i],NULL);
           }
  printf("\nacabo....\n");
return 0;

}

	
void *realizarTransferencia(void *p){
	/*Cada hilo debe seleccionar aleatoriamente dos cuentas*/
        printf("\nEn transferencia....");
        srand(rand());
        int nTranferencias=cantCorrer;
//el while es para el manejo de numero de transacciones que ara que sera igual el tiempo a corre
//que se ingresa como parametro
        while (nTranferencias>0){  
        int cuenta1=(rand()%nroCuentas)+1;
        int numcuenta1=(rand()%nroCuentas)+1;
        int numcuenta2=(rand()%nroCuentas)+1;
        int montoTrasferencia=(rand()%Cuentas[numcuenta1].monto)+1;
    	
	if(Cuentas[cuenta1].semaforo){
            Cuentas[cuenta1].semaforo=false;
//se uso un semaforo interno dentro de cada cuenta para poder ver si se puede acceder a ella
//si ingresa ala primero pero no puede entrar ala segunda libera la primera y vuelve a intentar 
//cuando las 2 tienen exito hace la transferencia
            if(Cuentas[numcuenta2].semaforo){
                Cuentas[numcuenta2].semaforo=false;
                printf("\n %d.%d.%d..\n",cuenta1,numcuenta2,montoTrasferencia);
                  printf("numero transfer %d \ncuenta2 antes %d \n",nTranferencias,Cuentas[numcuenta2].monto);
		Cuentas[cuenta1].monto=Cuentas[cuenta1].monto-montoTrasferencia;
                Cuentas[numcuenta2].monto=Cuentas[numcuenta2].monto+montoTrasferencia;
                  printf("cuenta 1 despues %d \n",Cuentas[cuenta1].monto);
                  printf("cuenta 2 despues %d \n",Cuentas[numcuenta2].monto);
              Cuentas[numcuenta2].semaforo=true;
              nTranferencias--;
            }
          Cuentas[cuenta1].semaforo=true;
        }	
        }
}


