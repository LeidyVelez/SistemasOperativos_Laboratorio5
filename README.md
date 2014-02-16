SistemasOperativos_Laboratorio5
===============================

Este repositorio contiene la información requerida para el laboratorio 5 del curso del sistemas Operativos, 2013-2


ENUNCIADO:
El objetivo de esta práctica es familiarizarse con el uso de las primitivas de sincronización (semáforos) 
y los problemas de concurrencia que pueden presentarse (condiciones de carrera, deadlocks) al construir 
aplicaciones multihuiladas. También se pretende explorar herramientas de control de versiones y de trabajo en
equipo.

Implemente un programa, en C, considerando

1. El programa se ejecuta así:
$./nombre_programa numeroDeHilos cantidad_tiempo_a_correr numero_cuentas valor_inicial

2. El hilo princial debe crear tantas cuentas como indique el parámetro numero_cuentas. 
El valor inicial de las cuentas estará especificado por valor_inicial.

3. En una cuenta se pueden realizar depósitos, retiros y transferencias.

4. El hilo principal creará la cantidad de hilos definida en numeroDeHilos. 
Cada hilo seleccionará de manera aleatoria dos cuentas y realizará transferencias de una cantidad o monto 
igualmente aleatorio. Cada hilo repetirá esta operación durante la cantidad de tiempo especificada en cantidad_tiempo_a_correr.

5. Al finalizar cantidad_tiempo_a_correr, el hilo principal deberá imprimir el valor de cada una de las cuentas y el balance total
de la sumatoria de todas las cuentas.

6. Realice un programa de prueba que llame automáticamente el programa anterior pero con diferentes vectores de prueba.
Dicho programa deberá leer la salida producida con cada vector de prueba y comprobar que el resultado es correcto.
Los vectores de prueba deberán estar almacenados en un archivo.

7. Corra el programa de prueba de así:
$./programa_prueba nombre_programa archivo_vectores_prueba

8. Imprima el resultado de cada vector indicando si pasó o no pasó.

9. Los vectores de prueba deberán ser almacenados por líneas, así:

numero_hilos cantidad_tiempo_a_correr numero_cuentas valor_inicial CANTIDAD_DE_REPETICIONES_DE_ESTE_VECTOR 

El parámetro CANTIDAD_DE_REPETICIONES_DE_ESTE_VECTOR indica la cantidad de veces que se deberá repetir este vector.

NOTAS:

1. Escriba la estrategia de solución INICIAL, explicando la estructura del programa y las ideas para resolver la práctica.
Explique cómo piensa utilizar las primitivas ofrecidas por el sistemas operativo para evitar condiciones de carrera y posibles interbloqueos.

2. Describa los problemas que encontró durante la solución de la práctica mostrando cómo se manifestaban, cómo los detectó y cómo los solucionó.

3. Describa como fue la solución final, explicando la estructura del programa y las ideas finalmente implementadas y funcionales.

4. Compare la solución inicial y la solución final.



