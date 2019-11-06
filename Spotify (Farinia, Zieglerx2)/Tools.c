#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

#include "TDA_Cancion.h"
#include "Tools.h"

#define arCancion "cancion.dat"

void mostrarArreglo(int a[], int validos)
{
    int i = 0;
    while(i < validos)
    {
        printf("%d - ", a[i]);
        i++;
    }
}
int cargarArregloDesdeArchivo(int a[], int DIM) /// CARGAMOS UN ARREGLO DE IDS, QUE ESTA ORDENADO.
{
    stCancion c;
    int i = 0;
    FILE * archi = fopen(arCancion, "rb");
    if(archi != NULL)
    {
        while(((i < DIM)) && fread(&c, sizeof(stCancion), 1, archi)>0)
        {
            a[i] = c.idCancion;
            i++;
        }
    }
    fclose(archi);

    return i;
}

int cargarArregloMitadInferior(int arregloCanciones[], int validos, int arregloInf[], int DIM)
{
    int i = 0;
    while(i < (validos / 2)) /// CARGAMOS EL ARREGLO INF HASTA LLEGAR A LA MITAD
    {
        arregloInf[i] = arregloCanciones[i];
        i++;
    }
    return i;
}

int cargarArregloMitadSuperior(int arregloCanciones[], int validos, int arregloSup[], int DIM)
{
    /// MISMA METODOLOGIA, CARGAMOS EL ARREGLO DESDE LA MITAD, PARA ARRIBA, HASTA EL FINAL
    int i = 0;
    while((i + validos/2) < validos)
    {
        arregloSup[i] = arregloCanciones[(i + (validos / 2))];
        i++;
    }
    return i;
}
void intercalarInferiorSuperior(int arregloCanciones[], int arregloInf[], int arregloSup[], int validos)
{
    int i = 0;
    int j = 0;
    while(i < validos)
    {
        arregloCanciones[i] = arregloInf[j]; /// AGREGAMOS 1 ELEMENTO DEL ARREGLO INFERIOR AL ARREGLO DESORDENADO
        i++;
        arregloCanciones[i] = arregloSup[j]; /// AGREGAMOS 1 ELEMENTO DEL ARREGLO SUPERIOR AL ARREGLO DESORDENADO
        i++;
        j++;
    }
}

int mezclarCanciones(int arregloCanciones[], int arregloInf[], int arregloSup[], int DIM) /// UTILIZAMOS LAS FUNCIONES PREVIAS PARA PODER MEZCLAR PREVIO A CARGAR EL ARBOL
{
    int validos = 0;

    /// CARGAMOS NUESTRO ARREGLO ORDENADO DE ID
    validos = cargarArregloDesdeArchivo(arregloCanciones, DIM);
    int validosReal = validos;

    validos = cargarArregloMitadInferior(arregloCanciones, validosReal, arregloInf, DIM);
    validos = cargarArregloMitadSuperior(arregloCanciones, validosReal, arregloSup, DIM);
    /// CARGAMOS INFERIOR Y SUPERIOR

    printf("Intercalando: \n");
    intercalarInferiorSuperior(arregloCanciones, arregloInf, arregloSup, validosReal);
    intercalarInferiorSuperior(arregloCanciones, arregloInf, arregloSup, validosReal);

    /// INTERCALAMOS 2 VECES, PARA QUE QUEDE TODAVIA MAS MEZCLADO, YA 3 PODRIA INTERCALARSE SI TUVIERAMOS MAS CANCIONES CARGADAS

    return validosReal;
}
