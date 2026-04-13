/*
Authors:
    - Eberle Javier,  MR: 23267
    - Iniguez Agustin, MR:22734
Date: 2024-06-11
Description:
    - El objetivo del presente trabajo consiste en realizar un programa en C, que permita calcular el
producto de dos matrices de números reales: C = A x B.

Dicho programa deberá recibir en la línea de comandos los siguientes parámetros:
- nombre del archivo que contiene los valores de la primera matriz (A)
- nombre del archivo que contiene los valores de la segunda matriz (B)
- nombre del archivo donde se almacenarán los valores de la matriz de resultados (C)
En el caso de que las matrices a multiplicar no sean de dimensiones compatibles para realizar el
producto, el programa debe finalizar con un mensaje de error en la pantalla.

*/


#include <stdio.h>
#include <stdlib.h>

//EPA ESTA FUNCION, ANDA
double ** leer_matriz (char *nombre_archivo, int *filas, int *columnas){
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL) {//si el archivo esta vacio o no se pudo abrir, se muestra un mensaje de error y se retorna NULL
        printf("Error al abrir el archivo %s\n", nombre_archivo);
        return NULL;
    }

fscanf(archivo, "%d", filas);
fscanf(archivo, "%d", columnas);//saca la información de un archivo abierto

    double **matriz = (double **)malloc(*filas * sizeof(double *));//reserva memoria para un arreglo de punteros a double, cada puntero representará una fila de la matriz El número de filas se da por el valor en la variable filas.       
    for (int i = 0; i < *filas; i++) {
        matriz[i] = (double *)malloc(*columnas * sizeof(double));
        for (int j = 0; j < *columnas; j++) {
            fscanf(archivo, "%lf", &matriz[i][j]);
        }
    }

    fclose(archivo);
    return matriz;
}

void liberar_memoria (double **matriz, int filas, int columnas) {

    for (int i = 0; i < filas; i++) { // Liberamos cada una de las filas individualmente
        free(matriz[i]); 
    }
    free(matriz);    //  Liberamos el arreglo de punteros principal
}

int multip( double **a, int fil_a, int col_a, double **b, int fil_b, int col_b, double ***c, int *fil, int *col ){
//ACA HAY QUE MULTIPLICAR Y GUARDAR LAS MATRICES,TAMBIEN HAY QUE ESCRIBIR EL ARCHIVO, LA LECTURA Y RESERVA DE MEMORIA ANDA BIEN
//0 si la operación se completó.
//1 si la operación no se re    alizó porque las dimensiones eran incompatibles.
//2 si la operación falló porque no se pudo asignar memoria dinámica para el resultado.
}


int main(int argc, char *argv[]) {//inicia el programa con los parametros de entrada
  if (argc != 4) {//si no es igual a 4, el programa no se ejecuta con los parametros correctos
        printf("Usar esta estructura: %s <archivoA.txt> <archivoB.txt> <archivoC.txt>\n", argv[0]);//aviso de uso
        return 1;//para verificar 
    }
 int FA,CA,FB,CB,i,j;//inicializacion de variables para filas y columnas de las matrices F=filas, C=columnas, A y B para las matrices
 FA=FB=CA=CB=0;//variables en 0           
 double **A = leer_matriz(argv[1], &FA, &CA);
    double **B = leer_matriz(argv[2], &FB, &CB);
if (A == NULL || B == NULL) {//si no se pudo leer alguna matriz, el error se mostro en la funcion leermatriz.
        return 1;
    }
printf("Matriz A (%d x %d):\n", FA, CA);// abro leo la matriz a
    for (i = 0; i < FA; i++) {//recorro la matriz
        for ( j = 0; j < CA; j++) {
            printf("%.2lf ", A[i][j]);//ponemos solo 2 decimales
        }
        printf("\n");
    }  
printf("Matriz B (%d x %d):\n", FB, CB);// abro leo la matriz b
    for ( i = 0; i < FB; i++) {
        for ( j = 0; j < CB; j++) {
            printf("%.2lf ", B[i][j]);//ponemos solo 2 decimales
        }
        printf("\n");
    } 

if(CA!=FB){
    printf("Error: Las dimensiones no son compatibles (%d x %d y %d x %d)\n", FA, CA, FB, CB);//verifico que se pueda multiplicar
    liberar_memoria(A, FA, CA);//libero memoria de a
    liberar_memoria(B, FB, CB);//libero memoria de b
    return 1;
}



    return 0;//funciono el programa   

}