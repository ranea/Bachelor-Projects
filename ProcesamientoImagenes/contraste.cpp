/*************************************************************************** 
 * Fichero: contraste.cpp
 * 
 * Formato: contraste <fichOri> <fichDest> <min> <max>
 *    <fichOri>   nombre del fichero que contiene la imagen original
 *    <fichDest>  nombre del fichero que contiene la imagen que se pretende llegar
 *    <min>       mínimo umbral de contraste
 *    <max>       máximo umbral de contraste
 *
 *
 **************************************************************************/

#include <iostream>
#include <cstdlib>
#include "imagen.h"
#include "utilidades.h"

using namespace std;


/*
 * Asignamos el primer píxel como el valor mínimo de gris. 
 * Recorremos la imagen al completo y determinamos el mínimo
 * valor de gris de la imagen 
 */
template <class T>
int min_imag (const Imagen<T> &imag)
{
   int min = imag(0,0);

   for (int i = 0; i < imag.num_filas(); i++)
      for (int j = 0; j < imag.num_columnas(); j++)
         if (imag(i,j) < min)
            min = imag(i,j);

   return min;
}

/* 
 * Asignamos el primer píxel como el valor máximo de gris. 
 * Recorremos la imagen al completo y determinamos el máximo
 * valor de gris de la imagen
 */
template <class T>
int max_imag (const Imagen<T> &imag)
{


   int max = imag(0,0);

   for (int i = 0; i < imag.num_filas(); i++)
      for (int j = 0; j < imag.num_columnas(); j++)
         if (imag(i,j) > max)
            max = imag(i,j);

   return max;
}

/* 
 * Aplicamos una transformación lineal (redondeada al entero más próximo)
 * sobre todos los píxeles de la imagen para conseguir una imagen con más 
 * contraste (blancos más blancos y negros más negros)
 */

Imagen<unsigned char> contraste(const Imagen<unsigned char> &orig,int min, int max)
{
   Imagen<unsigned char> imag(orig);
   int a = min_imag(imag);
   int b = max_imag(imag);
   double constante = (max-min)/(b-a);

   for (int i = 0; i < imag.num_filas(); i++)
      for (int j = 0; j < imag.num_columnas(); j++)
         imag(i,j) = (int) min + constante * (imag(i,j) - a) + 0.5;

   return imag;
}

int main(int argc, char const *argv[])
{
   int min, max;
   const char *origen, *destino;

   if (argc != 5){
      cerr << "Error: Numero incorrecto de parametros.\n";
      cerr << "Uso: contraste <fichOri> <fichDest> <min> <max>\n";
      exit (1);
   }
   /* Leemos los argumentos del main */
   origen = argv[1];
   destino = argv[2];
   min = atoi(argv[3]);
   max = atoi(argv[4]);

   /* Si min > max, debemos intercambiarlos */

   if (min > max)
   {
      int aux;
      aux = min;
      min = max;
      max = aux;
   }

   /* Mostramos los ficheros origen y destino */
   cout << endl;
   cout << "Fichero origen: " << origen << endl;
   cout << "Fichero resultado: " << destino << endl << endl;

   /* Trabajamos la imagen con las funciones auxiliares */
   Imagen<unsigned char> img(leeImagen(origen));
   escribeImagen(destino,contraste(img,min,max));

   return 0;
}