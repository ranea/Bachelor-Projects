/*************************************************************************** 
 * Fichero: morphing.cpp
 * 
 * Formato: morphing <fichOri> <fichDest> <k> <pref>
 *    <fichOri>  nombre del fichero que contiene la imagen original
 *    <fichDest> nombre del fichero que contiene la imagen que se pretende llegar
 *    <k>  numero de iteraciones para realizar la transformacion
 *    <pref>  prefijo de las imagenes que forman el video de salida
 *
 *
 **************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "imagen.h"
#include "video.h"
#include "utilidades.h"


using namespace std;

/* 
 * Realiza un morphing de img_ori a img_dest
 * Devuelve un video con las proceso completo de transformacion
 */
template <class T>
Video <T> morphing(const Imagen<T>& img_ori, const Imagen<T>& img_dest, int iteraciones)
{
   Video<T> morph_V;

   int nf = img_ori.num_filas();
   int nc = img_ori.num_columnas();
   Imagen<T> img_aux(nf,nc);

   for (int k=0; k<=iteraciones; ++k)
   {
      for (int i = 0; i < nf; ++i)
         for (int j = 0; j < nc; ++j)
            img_aux(i,j) = ( (iteraciones-k)*img_ori(i,j) + k*img_dest(i,j) )/iteraciones;           

      morph_V.Insertar(morph_V.end(),img_aux); 
   }

   return morph_V;
}

int main(int argc, char const *argv[])
{
   if (argc != 5){
      cerr << "Error: Numero incorrecto de parametros.\n";
      cerr << "Uso: morphing <fichOri> <fichDest> <n> <pref> \n";
      exit (1);
   }

   // Leemos los argumentos del main
   const char *origen = argv[1];
   const char *destino = argv[2];
   const char *prefijo = argv[4];
   int iteraciones = atoi(argv[3]);


   // Leemos las imagenes
   cout << endl;
   Imagen<unsigned char> img_ori(leeImagen(origen));
   Imagen<unsigned char> img_dest(leeImagen(destino));
   cout << endl;


   // Comprobamos que tengan la misma dimension
   if (img_ori.num_filas() != img_dest.num_filas() 
         || img_dest.num_columnas() != img_dest.num_columnas())
   {
      cout << "Error: las imagenes deben tener la misma dimension" << endl;
      exit(3);
   }


   // Realizamos el morphing
   Video<unsigned char> morph_V(morphing(img_ori,img_dest,iteraciones));


   // Escribimos la imagenes del video
   escribeVideo(prefijo,morph_V);


   return 0;
}