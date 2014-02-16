#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

/***************************Variables globales******************************************/
FILE *file;
int tam=20; /*Número máximo de parámetros*/
int i=0;
int* parametrosMain;
char cadena[150], nroHilos[5], cantidadTiempoCorrer[5], numeroCuentas[5], valorInicial[30], cantidadRepeticiones[5];
/*************************************************************************************/


int main(int argc, char *argv[])
{
	int k;  
  	char cadena[1024], *p;
	FILE *file;

	parametrosMain = (int*)malloc(tam*sizeof(int));
		if (parametrosMain==NULL){perror("Problemas reservando memoria");exit (1);}
	/*Inicialización del vector*/   
		for(k=0; k<=tam; k++)     {
		parametrosMain[k]=(0);
		}
	/*Manejo de archivo*/
        file=fopen("vectorPruebas.txt","r");
	    if(file==NULL)return(printf("Error al abrir, el archivo no existe!n"));
	k=0;
	 while((fgets(cadena,1024,file)) != NULL)    {       
		 p=strtok(cadena," ");
		while(p!=NULL)
		{
		   parametrosMain[k]=atof(p);
		    p=strtok(NULL," ");
		    k++;
	     }

   	 }
tam=k-1;
fclose(file);       
/***********Uso de la función execl para llamar al programa que proceso los vectores de prueba********************/
	strcpy(cadena, argv[0]); /**Guardo el nombre del archivo ejecutable**/
	/*Se llama la función execl  con los parámetros numero_hilos cantidad_tiempo_a_correr numero_cuentas valor_inicial 		CANTIDAD_DE_REPETICIONES_DE_ESTE_VECTOR */
	sprintf(nroHilos, "%d", parametrosMain[0]); 
	sprintf(cantidadTiempoCorrer, "%d", parametrosMain[1]);
	sprintf(numeroCuentas, "%d", parametrosMain[2]);
	sprintf(valorInicial, "%d", parametrosMain[3]);
	sprintf(cantidadRepeticiones, "%d", parametrosMain[4]); 
	strcat(cadena," ");	
	strcat(cadena, nroHilos);
	strcat(cadena," ");
	strcat(cadena, cantidadTiempoCorrer);
	strcat(cadena, " ");
	strcat(cadena, numeroCuentas );
	strcat(cadena, " ");
	strcat(cadena, valorInicial );
	strcat(cadena, " ");
	strcat(cadena, cantidadRepeticiones );
	printf("%s", cadena);
	execl("/bin/sh","/bin/sh","-c",cadena,NULL);

return 0;
}

