/*************************************************************************** 
 * Fichero: umbralizar.cpp
 * 
 * Formato: umbralizar <fichOri> <fichDest> <T1> <T2>
 *    <fichOri>  nombre del fichero que contiene la imagen original
 *    <fichDest> nombre del fichero que contiene la imagen que se pretende llegar
 *    <T1>       mínimo valor de umbral
 *    <T2>       máximo valor de umbral
 *
 *
 **************************************************************************/


#include <iostream>
#include <cstdlib>
#include "utilidades.h"

using namespace std;

/*
 * Ponemos el valor del píxel al máximo (blanco) si dicho valor
 * está fuera de dos valores umbral 
 */
Imagen<unsigned char> umbralizar(const Imagen<unsigned char> &orig,int t1, int t2)
{
   Imagen<unsigned char> imag(orig);

   for (int i = 0; i < imag.num_filas(); i++)
      for (int j = 0; j < imag.num_columnas(); j++)
         if (!(imag(i,j) > t1 && imag(i,j) < t2 ))
            imag(i,j) = 255;

   return imag;
}

int main(int argc, char const *argv[])
{
   int t1, t2;
   const char *origen, *destino;

   if (argc != 5){
      cerr << "Error: Numero incorrecto de parametros.\n";
      cerr << "Uso: umbralizar <fichOri> <fichDest> <T1> <T2>\n";
      exit (1);
   }

   /* Leemos los argumentos del main */
   origen = argv[1];
   destino = argv[2];
   t1 = atoi(argv[3]);
   t2 = atoi(argv[4]);

   /* Mostramos la ruta origen y destino de los ficheros */
   cout << endl;
   cout << "Fichero origen: " << origen << endl;
   cout << "Fichero resultado: " << destino << endl;

   /* Transformamos la imagen usando las funciones auxiliares */
   Imagen<unsigned char> img(leeImagen(origen));
   escribeImagen(destino,umbralizar(img,t1,t2));

   return 0;
}