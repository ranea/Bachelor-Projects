/*************************************************************************** 
 * Fichero: icono.cpp
 * 
 * Formato: icono <fichE> <fichS> <nf> <nc>
 *    <fichE> nombre del fichero que contiene la imagen original
 *    <fichS> nombre del fichero donde se guarda el icono
 *    <nf> <nc> número de filas y columnas del icono resultante
 *
 *
 **************************************************************************/

#include <iostream>
#include <stdlib.h>
#include "imagen.h"
#include "utilidades.h"

using namespace std;

/**
 * Devuelve la subimagen de esquiza superior derecha (x,y) 
 * de tamaño orden x orden
 */ 
template <class T>
Imagen<T> subImagen(const Imagen<T>& img, int x, int y, int orden)
{
   Imagen<T> sub_img(orden,orden);

   for (int i = 0; i < orden; ++i)
      for (int j = 0; j < orden; ++j)
         sub_img(i,j) = img(x+i,y+j);

   return sub_img;
}


/**
 * Devuelve la media aritmetica de los elementos de la imagen
 */
template <class T>
int mediaAritmetica(const Imagen<T>& img)
{
   int nf = img.num_filas();
   int nc = img.num_columnas();
   int media = 0;

   for (int i = 0; i < nf; ++i)
      for (int j = 0; j < nc; ++j)
         media += img(i,j);

   return media/(nf*nc);
}


/**
 * Devuelve el icono de una imagen
 */
template <class T>
Imagen<T> creaIcono(const Imagen<T>& img, int icono_nf, int icono_nc)
{
   int orden = img.num_filas()/icono_nf; /**< Orden de reduccion */

   Imagen<T> icono_img(icono_nf,icono_nc);

   for (int i = 0; i < icono_nf; ++i)
      for (int j = 0; j < icono_nc; ++j){
         Imagen<T> sub_img(subImagen(img,i*orden,j*orden,orden));
         icono_img(i,j) = mediaAritmetica(sub_img);
      }
         
   return icono_img;
}

int main(int argc, char const *argv[])
{
   if (argc != 5){
      cerr << "Error: Numero incorrecto de parametros.\n";
      cerr << "Uso: icono <fichE> <fichS> <nf> <nc>\n";
      exit (1);
   }

   // Leemos los argumentos del main
   const char *origen = argv[1];
   const char *destino = argv[2];
   int icono_nf = atoi(argv[3]);
   int icono_nc = atoi(argv[4]);


   // Leemos la imagen
   cout << endl;
   Imagen<unsigned char> img(leeImagen(origen));
   cout << endl;


   // Procesamos la imagen
   Imagen<unsigned char> icono_img(creaIcono(img,icono_nf,icono_nc));


   // Imprimimos la imagen
   escribeImagen(destino,icono_img);

   return 0;
}