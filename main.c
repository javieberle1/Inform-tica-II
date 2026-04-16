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

// Incluimos librerías
#include <stdio.h>
#include <stdlib.h>

// Función para leer matriz desde el archivo y guardarla para operar
double **leer_matriz(char *nombre_archivo, int *filas, int *columnas)
{
    // Abre el archivo para lectura
    FILE *archivo = fopen(nombre_archivo, "r");

    // Verifica que se haya podido abrir correctamente
    if (archivo == NULL)
    {
        printf("Error al abrir el archivo %s\n", nombre_archivo);
        return NULL;
    }

    // Lee linea a linea el archivo
    fscanf(archivo, "%d", filas);
    fscanf(archivo, "%d", columnas);

    // Pide memoria para un doble puntero a double (La matriz), el primer puntero representará una fila de la matriz y el segundo puntero la posicion i de esa fila.
    double **matriz = (double **)malloc(*filas * sizeof(double *));

    // Este bucle genera tantas filas como se hayan leido del archivo
    for (int i = 0; i < *filas; i++)

    {
        // Se solicita memoria para todos los elementos de la fila i (un arreglo de doubles)
        matriz[i] = (double *)malloc(*columnas * sizeof(double));

        // Este bucle genera columnas segun tenga la matriz leida
        for (int j = 0; j < *columnas; j++)
        {
            // Lee el archivo y guarda el dato en la matriz indicada
            fscanf(archivo, "%lf", &matriz[i][j]);
        }
    }

    // Se cierra el archivo
    fclose(archivo);

    // Retornamos la matriz cargada
    return matriz;
}

// Función liberar memoria
void liberar_memoria(double **matriz, int filas, int columnas)
{

    // Libera la memoria solicitada de cada una de las filas de la matriz
    for (int i = 0; i < filas; i++)
    {
        // Liberamos cada una de las filas individualmente
        free(matriz[i]);
    }

    //  Liberamos el arreglo de punteros principal
    free(matriz);
}

// Función para multiplicar las matrices
int multip(double **a, int fil_a, int col_a, double **b, int fil_b, int col_b, double ***c, int *fil, int *col)
{
    // ACA HAY QUE MULTIPLICAR Y GUARDAR LAS MATRICES,TAMBIEN HAY QUE ESCRIBIR EL ARCHIVO, LA LECTURA Y RESERVA DE MEMORIA ANDA BIEN
    // 0 si la operación se completó.
    // 1 si la operación no se realizó porque las dimensiones eran incompatibles.
    // 2 si la operación falló porque no se pudo asignar memoria dinámica para el resultado.

    // Teniendo en cuenta que la multiplicacion es AxB = C donde las columnas de A deben ser iguales a las filas de B es decir --> col_a = fil_b

    // Preguntamos si la condición para poder realizar la operacion es verdadera
    if (col_a == fil_b)
    {

        // Esto hace que el main reciba los datos correctamente
        *fil = fil_a;
        *col = col_b;

        // Asignamos memoria a cada fila de la matric resultado (C)
        *c = (double **)malloc(fil_a * sizeof(double *));

        // Recorremos columna a columan
        for (int i = 0; i < fil_a; i++)
        {
            (*c)[i] = (double *)malloc(col_b * sizeof(double));
        }

        // Recorremos al matriz C
        for (int i = 0; i < fil_a; i++)
        {
            for (int j = 0; j < col_b; j++)
            {
                (*c)[i][j] = 0;

                for (int k = 0; k < col_a; k++)
                {

                    (*c)[i][j] += (a)[i][k] * (b)[k][j];
                }
            }
        }

        return 0;
    }
    else if (col_a != fil_b)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

// inicia el programa con los parametros de entrada
int main(int argc, char *argv[])
{
    // Como le pedimos 4 argumentos, si no se los pasamos el programa no se debe ejecutar
    if (argc != 4)
    {

        // Aviso de como se usa el programa
        printf("Usar esta estructura: %s <archivoA.txt> <archivoB.txt> <archivoC.txt>\n", argv[0]);
        // para verificar
        return 1;
    }

    // Inicializacion de variables para filas y columnas de las matrices
    // F=filas, C=columnas, A y B para las matrices
    int FA, CA, FB, CB, i, j;

    // Inicializamos las variables en 0
    FA = FB = CA = CB = 0;

    // Creamos dos punteros dobles a double y llamamos a la funcion leer matriz
    double **A = leer_matriz(argv[1], &FA, &CA);
    double **B = leer_matriz(argv[2], &FB, &CB);

    if (A == NULL || B == NULL)
    {
        // si no se pudo leer alguna matriz, el error se mostro en la funcion leermatriz.
        return 1;
    }

    // Aviso de que se esta leyendo la matriz A
    printf("Matriz A (%d x %d): \n", FA, CA);

    // Bucle para recorrer la matriz A
    for (i = 0; i < FA; i++)
    {
        for (j = 0; j < CA; j++)
        {
            // Imprimimos en pantalla el elemento ij de la matriz A con dos decimales
            printf("%.2lf ", A[i][j]);
        }
        printf("\n");
    }

    // Aviso de que se esta leyendo la matriz B
    printf("Matriz B (%d x %d):\n", FB, CB);

    // Bucle para recorrer la matriz B
    for (i = 0; i < FB; i++)
    {
        for (j = 0; j < CB; j++)
        {
            // Imprimimos en pantalla el elemento ij de la matriz B con dos decimale
            printf("%.2lf ", B[i][j]);
        }
        printf("\n");
    }

    // Puntero a c, la matriz nueva
    double **C = NULL;

    // Variables para guardas las filas y columnas de la matriz nueva
    int FC, CC;

    // Llamamos a la funcion multiplicar
    int salida = multip(A, FA, CA, B, FB, CB, &C, &FC, &CC);

    // Verificamos con un condicional que paso con la funcion multiplicar

    // Si devolvio cero la operacion se realizo
    if (salida == 0)
    {
        // Mostramos un mensaje que se realizo
        printf("La operación se realizo con exito");

        // Imprimimos la matriz C resultado

        printf("La matriz resultado es: \n");

        for (i = 0; i < FC; i++)
        {
            for (j = 0; j < CC; j++)
            {
                // Imprimimos en pantalla el elemento ij de la matriz B con dos decimale
                printf("%.2lf ", C[i][j]);
            }
            printf("\n");
        }

        // Guardamos la matriz C en el archivo nuevo

        FILE *archivo_resultado = fopen(argv[3], "w");

        // Escribimos el formado del archivo primero
        fprintf(archivo_resultado, "%d %d\n", FC, CC);

        // Bucle para recorrer la matriz e ir imprimiendo en el archivo
        for (i = 0; i < FC; i++)
        {
            for (j = 0; j < CC; j++)
            {
                // Imprimimos el valor en la posicion [i][j]
                fprintf(archivo_resultado, "%.2lf ", C[i][j]);
            }
            // Salto de linea para mantener el orden
            fprintf(archivo_resultado, "\n");
        }

        fclose(archivo_resultado);
    }
    else if (salida == 1)
    {
        printf("Las dimensiones de las matrices no son las correctas");
    }
    else
    {
        printf("No se pudo solicitar la cantidad de memoria para las matrices");
    }

    // Liberamos memoria de todas las matrices

    liberar_memoria(A, FA, CA);
    liberar_memoria(B, FB, CB);
    if (C != NULL)
    {
        liberar_memoria(C, FC, CC);
    }

    // Retornamos 0 ya que funciono el programa
    return 0;
}