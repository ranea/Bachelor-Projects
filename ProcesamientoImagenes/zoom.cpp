/*************************************************************************** 
 * Fichero: zoom.cpp
 * 
 * Formato: zoom <fichE> <fichS> <x1> <y1> <x2> <y2>
 *    <fichE> nombre del fichero que contiene la imagen original
 *    <fichS> nombre del fichero que contedrá el resultado del zoom
 *    <(x1> <y1> coordenadas de la esquina superior izquierda del trozo de imagen
 *    <(x2> <y2> coordenadas de la esquina inferior derecha del trozo de imagen
 *
 * Nota: El trozo ha de ser cuadrado
 *
 **************************************************************************/

#include <iostream>
#include <stdlib.h>
#include "imagen.h"
#include "utilidades.h"

using namespace std;


/**
 * Comprueba si el siguiente recuadro es un cuadrado 
 *     (x1,y1)........
 *        ·          ·
 *        ·          ·
 *        ·........(x2,y2)
 */
bool esCuadradoValido(int x1,int y1,int x2,int y2)
{
   return (x2-x1 == y2-y1) && x2-x1>0 && x1>=0 && y1>=0;
}


/**
 * Devuelve la subimagen cuadrada
 *     (x1,y1).....
 *        ·       ·
 *        ·       ·
 *        ·....(x2,y2)
 */
template <class T>
Imagen<T> subImagen(const Imagen<T>& img, int x1, int y1, int x2, int y2)
{
   int dim = x2-x1+1;

   Imagen<T> sub_img(dim,dim);

   for (int i = 0; i < dim; ++i)
      for (int j = 0; j < dim; ++j)
         sub_img(i,j) = img(x1+i,y1+j);

   return sub_img;
}


/**
 * Devuelve la imagen ampliada(zoom) de img
 */
template <class T>
Imagen<T> zoom(const Imagen<T>& img)
{
   int img_nf = img.num_filas();
   int img_nc = img.num_columnas();

   Imagen<T> zoom_img(2*img_nf-1, 2*img_nc-1);

   //Introducimos los elementos de la imagen original
   for (int i = 0; i < img_nf; ++i)
      for (int j = 0; j < img_nc; ++j)
         zoom_img(2*i,2*j) = img(i,j);

   int zoom_nf = zoom_img.num_filas();
   int zoom_nc = zoom_img.num_columnas();

   // Rellenamos los huecos con la media (redondeada) de los valores vecinos
   for (int i = 0; i < zoom_nf; ++i)
      for (int j = 1; j < zoom_nc; j+=2)
         zoom_img(i,j) =  (int) (zoom_img(i,j-1)+zoom_img(i,j+1))/2.0 + 0.5;

   for (int i = 1; i < zoom_nf; i+=2)
      for (int j = 0; j < zoom_nc; j++)
         zoom_img(i,j) =  (int) (zoom_img(i+1,j)+zoom_img(i-1,j))/2.0 + 0.5;


   return zoom_img;
}

int main(int argc, char const *argv[])
{
   if (argc != 7){
      cerr << "Error: Numero incorrecto de parametros.\n";
      cerr << "Uso: zoom <fichE> <fichS> <x1> <y1> <x2> <y2>\n";
      exit (1);
   }

   // Leemos los argumentos del main
   const char *origen = argv[1];
   const char *destino = argv[2];

   int x1 = atoi(argv[3]);
   int y1 = atoi(argv[4]);
   int x2 = atoi(argv[5]);
   int y2 = atoi(argv[6]);


   // Leemos la imagen
   cout << endl;
   Imagen<unsigned char> img(leeImagen(origen));
   cout << endl;


   // Verificamos el cuadrado pasado por argumento
   if(!esCuadradoValido(x1,y1,x2,y2)){
      cout << "Error: los pares x1,y1 x2,y2 deben formar un cuadrado" << endl; 
      cout << "El punto x1,y1 debe referenciar a la esquiza superior izquierda" << endl;
      cout << "   y el punto x2,y2 debe referenciar a la esquiza inferior derecha." << endl;
      exit(3);     
   }
   if(x2>=img.num_filas() || y2>=img.num_columnas()){
      cout << "Error, los pares x1,y1 x2,y2 deben pertenecer a " << origen << endl;
      exit(3);
   }
   cout << "(x1,y1): (" << x1 << "," << y1 << ")" << endl;
   cout << "(x2,y2): (" << x2 << "," << y2 << ")" << endl;


   // Procesamos la imagen
   Imagen<unsigned char> sub_img(subImagen(img,x1,y1,x2,y2));
   Imagen<unsigned char> zoom_img(zoom(sub_img));


   // Imprimimos la imagen
   escribeImagen(destino,zoom_img);

   return 0;
}