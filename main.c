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
#include <semaphore.h>


/*Variables globales y protipos de funciones*/
#define MAX_THREADS     6 
#define MAX_CUENTAS 10 

sem_t sem1;
/*----------------------------------------------------------------------------------------*/
void *realizarTransferencia(void *p);
/*----------------------------------------------------------------------------------------*/
int i, rndCuenta, nroHilos, cantCorrer, nroCuentas, valorIni=0,nCuentas[1],sumbalance=0;;
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
  } t_Cuentas;
t_Cuentas Cuentas[MAX_CUENTAS];

/*----------------------------------------------------------------------------------------*/

int main(int argc, char *argv[]){
	//variables semaforo
	sem_init(&sem1,0,1);
	srand(atoi(argv[5]));
	//variables guardado de datos
        int Id_Memoria;
        int *Memoria = NULL;
        const int SIZE = 1024;
        key_t Clave=123;

	
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
	//printf("Creando Cuentas...\n"); 
	for(i=0; i<=nroCuentas;i++){
		Cuentas[i].idCuenta=i; /*Guardo el identificador de la cuenta*/
		Cuentas[i].monto=valorIni; /*Guardo el valor inicial de cada cuenta*/
	}
            for (i=0; i<nroHilos; i++) 
      		{  
			pthread_create(&h[i],NULL,realizarTransferencia,NULL);
		      } 
            for (i=0; i<nroHilos; i++) 
      		{ 
                  pthread_join(h[i],NULL);
                }
        /*Se Imprime el valor de las cuentas y el balance total*/  
        printf("valores de las cuentas al final \n\n");
        
        //muestro el valor final de cada cuenta y la suma
      for(i=0;i<nroCuentas;i++){
          printf("Cuenta%d : %d \n",i+1,Cuentas[i].monto);
          sumbalance=sumbalance+Cuentas[i].monto;
       }
	printf("\nBalance total de las cuentas: %d", sumbalance);
	
      //abro memoria para guardar si pasó el vector o no
      Id_Memoria = shmget(Clave, SIZE, IPC_EXCL | 0666 );
      if (Id_Memoria == -1) 
       {  
        printf("No consigo Id para memoria compartida\n");
        exit (0);
       }
      Memoria = (int *)shmat (Id_Memoria, (int *)0, 0);
     if (Memoria == NULL) 
       { 
         printf("No consigo memoria compartida");
         exit (0);
     }
     Memoria[0] = Id_Memoria;
         if(sumbalance==nroCuentas*valorIni){//verifico si el dinero es el mismo
            Memoria[atoi(argv[5])] = 1;//apruebo
         }else{
              Memoria[atoi(argv[5])] = 0;//desapruebo
          }
          sem_destroy(&sem1);
return 0;

}

	
void *realizarTransferencia(void *p){
	/*Cada hilo debe seleccionar aleatoriamente dos cuentas*/

        int nTranferencias=cantCorrer;
//el while es para el manejo de número de transacciones que hará que será igual el tiempo que corre
	//que se ingresa como parámetro
        int cuenta1, numcuenta1, numcuenta2, montoTrasferencia;
        while (nTranferencias>0){  
         cuenta1=(rand()%nroCuentas);
        numcuenta1=(rand()%nroCuentas);
        numcuenta2=(rand()%nroCuentas);
        sem_wait(&sem1);
                montoTrasferencia=(rand()%Cuentas[cuenta1].monto);
		Cuentas[cuenta1].monto=Cuentas[cuenta1].monto-montoTrasferencia;
                Cuentas[numcuenta2].monto=Cuentas[numcuenta2].monto+montoTrasferencia;
        sem_post(&sem1);
              nTranferencias--;
	
        }
}



