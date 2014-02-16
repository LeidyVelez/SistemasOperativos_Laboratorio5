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
int i=0,j;
int* parametrosMain;
char cadena[150], nroHilos[5], cantidadTiempoCorrer[5], numeroCuentas[5], valorInicial[30], cantidadRepeticiones[5],vector[5],iteracion[5];
/*************************************************************************************/


int main(int argc, char *argv[])
{
        //variables guardado de datos
        int Id_Memoria;
        int *Memoria = NULL;
        const int SIZE = 1024;
        key_t Clave=123;
        //creacion de memoria compartida
        Id_Memoria = shmget(Clave, SIZE, IPC_CREAT | 0666 );
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


	int k;  
  	char cadena[1024], *p;
	FILE *file;
        pid_t hilo_rep;
        int status_n;

	parametrosMain = (int*)malloc(tam*sizeof(int));
		if (parametrosMain==NULL){perror("Problemas reservando memoria");exit (1);}
	/*Inicialización del vector*/   
		for(k=0; k<=tam; k++)     {
		parametrosMain[k]=(0);
		}
	/*Manejo de archivo*/
        file=fopen(argv[2],"r");
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
for(j=0;j<sizeof(parametrosMain);j++){
/***********Uso de la función execl para llamar al programa que proceso los vectores de prueba********************/
	strcpy(cadena, "./");
	strcat(cadena, argv[1]);/**Guardo el nombre del archivo ejecutable**/
	/*Se llama la función execl  con los parámetros numero_hilos cantidad_tiempo_a_correr numero_cuentas valor_inicial 		CANTIDAD_DE_REPETICIONES_DE_ESTE_VECTOR */
	sprintf(nroHilos, "%d", parametrosMain[j*5]); 
	sprintf(cantidadTiempoCorrer, "%d", parametrosMain[(j*5)+1]);
	sprintf(numeroCuentas, "%d", parametrosMain[(j*5)+2]);
	sprintf(valorInicial, "%d", parametrosMain[(j*5)+3]);
	//sprintf(cantidadRepeticiones, "%d", parametrosMain[4]); 
	strcat(cadena," ");	
	strcat(cadena, nroHilos);
	strcat(cadena," ");
	strcat(cadena, cantidadTiempoCorrer);
	strcat(cadena, " ");
	strcat(cadena, numeroCuentas );
	strcat(cadena, " ");
	strcat(cadena, valorInicial );

	 //ejecuto el programa las veces q me indique el archivo
        for(i=0;i<parametrosMain(j*5)+4];i++){
           hilo_rep=fork();
           if(hilo_rep==0){
             sprintf(vector, "%d", ((j+1)*2)+i); //agrego este dato para el guardado de memoria
             strcat(cadena, " ");
	     strcat(cadena, vector );
 	     //printf("%s \n", cadena);
	     execl("/bin/sh","/bin/sh","-c",cadena,NULL);
           }
         }
        for(i=0;i<parametrosMain[(j*5)+4];i++){
           wait(&status_n);
          }
}
for(j=0;j<sizeof(parametrosMain);j++){
         for(i=0;i<parametrosMain[(j*5)+4];i++){
              if(Memoria[((j+1)*2)+i]==1){//saco el dato que guarde en el progama main de todos los hilos
              printf("\nVector #%d en la iter %d : PASO\n",j+1, i+1);
                  }else{
              printf("\nVector #%d en la iter %d : NO PASO\n",j+1, i+1);
              }
         }
}   
       printf("termino programa \n");
       
shmctl(Memoria[0], IPC_RMID, (struct shmid_ds *)NULL);

return 0;
}

