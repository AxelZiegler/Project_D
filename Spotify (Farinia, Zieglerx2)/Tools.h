#define TOOLS_H_INCLUDED

#include "TDA_Cancion.h"
#include "TDA_ListaCancion.h"

/// LIBRERIA DE HERRAMIENTAS UTILES

void mostrarArreglo(int a[], int validos);
void intercalarInferiorSuperior(int arregloCanciones[], int arregloInf[], int arregloSup[], int validos);

int cargarArregloDesdeArchivo(int a[], int DIM);
int cargarArregloMitadInferior(int arregloCanciones[], int validos, int arregloInf[], int DIM);
int cargarArregloMitadSuperior(int arregloCanciones[], int validos, int arregloSup[], int DIM);
int mezclarCanciones(int arregloCanciones[], int arregloInf[], int arregloSup[], int DIM);

#endif // TOOLS_H_INCLUDED
