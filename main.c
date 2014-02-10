+	#include<stdio.h>
+	#include<stdlib.h>
+	#include<unistd.h>
+	#include<sys/types.h>
+	#include<string.h>
+	#include <sys/ipc.h>
+	#include <sys/shm.h>
+	#include <pthread.h>
+	
+	
+	/*Variables globales y protipos de funciones*/
+	#define MAX_THREADS     6 //DEBE MODIFICARSE PARA CAPTURARSE EN TIEMPO DE COMPILACIÓN!!!
+	#define MAX_CUENTAS 10 //TAMBIÉN HAY QUE MODIFICARLA!!!!
+	/*----------------------------------------------------------------------------------------*/
+	void *realizarTransferencia(void *p);
+	/*----------------------------------------------------------------------------------------*/
+	int i, rndCuenta, nroHilos, cantCorrer, nroCuentas, valorIni=0;
+	char *numeroHilos, *cantidadTiempoCorrer, *valorInicial, *numeroCuentas, *nombreArchivo;
+	char final[10];
+	
+	/*----------------------------------------------------------------------------------------*/
+	 /* tipo de datos y tabla con los parametros*/
+	/*Esta tabla contendrá los identificadores de cada hilo, se pasarán por referencia*/
+	typedef struct
+	  {   
+	   int idThread; 
+	  } t_Threads;
+	t_Threads Threads[MAX_THREADS]; 
+	 
+	/*----------------------------------------------------------------------------------------*/
+	
+	  /* tipo de datos y tabla con los parametros*/
+	/*Esta tabla contendrá los identificadores y monto de cada cuenta*/
+	typedef struct                    
+	  {   
+	   int idCuenta; 
+	   int monto;
+	  } t_Cuentas;
+	t_Cuentas Cuentas[MAX_CUENTAS];
+	
+	/*----------------------------------------------------------------------------------------*/
+	
+	
+	int main(int argc, char *argv[]){
+		pthread_t h;
+		/*Captura de parámetros*/
+		numeroHilos= argv[1];
+		cantidadTiempoCorrer=argv[2]; 
+		numeroCuentas=argv[3];	
+		valorInicial=argv[4];
+		if((numeroHilos==NULL )	|| (cantidadTiempoCorrer==NULL ) || (numeroCuentas==NULL) || (valorInicial==NULL)){
+		printf("Ingrese los valores de los parámetros!!");
+		return;
+		}
+		nroHilos=atoi(numeroHilos);
+		cantCorrer= atoi(cantidadTiempoCorrer);
+		nroCuentas=atoi(numeroCuentas);
+		valorIni=atoi(valorInicial);
+		if((nroHilos<=0)|| (cantCorrer<=0)|| (nroCuentas<=0) || (valorIni<=0)){printf("Ingrese valores de parámetros mayores que cero!!");return;}
+		printf("Creando Cuentas...\n"); 
+		for(i=0; i<=nroCuentas;i++){
+			Cuentas[i].idCuenta=i; /*Guardo el identificador de la cuenta*/
+			Cuentas[i].monto=valorIni; /*Guardo el valor inicial de cada cuenta*/
+		}
+		printf("Creando threads...\n"); 
+		    for (i=0; i<nroHilos; i++) 
+	      		{ 
+				Threads[i].idThread= i; 
+				pthread_create(&h,NULL,realizarTransferencia,(void *)&Threads[i]);
+			      } 
+	
+	return 0;
+	
+	}
+	
+	
+	void *realizarTransferencia(void *p){
+		/*Cada hilo debe seleccionar aleatoriamente dos cuentas*/
+			printf("\nEn transferencia....");
+		t_Threads *datos;
+	    	datos= (t_Threads *)p;
+			for(i=0; i<2; i++)
+				rndCuenta=(rand()%5 + 1);
+				//se ubica la cuenta escogida para hacer la transferencia
+	
+			}
+	
