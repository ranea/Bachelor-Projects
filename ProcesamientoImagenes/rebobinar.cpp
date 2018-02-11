/*************************************************************************** 
 * Fichero: rebobinar.cpp
 * 
 * Formato: rebobinar <prefOri> <nframes> <prefDest> 
 *    <prefOri>  nombre del prefijo que contiene las imágenes originales
 *    <nframes>  numero de frames del vídeo original
 *    <prefDest> nombre del prefijo que van a tener las imágenes en orden inverso
 *    
 * 
 *
 **************************************************************************/

#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "video.h"
#include "utilidades.h"


using namespace std;

/*
 * Rebobina el vídeo pasado como argumento colocando cada una de las imágenes del vídeo
 * en un vídeo auxiliar empezando desde el final.
 */

template <class T>
Video <T> rebobinar (const Video<T> &v)
{
   Video<T> aux;
   
   typename Video<T>::const_iterator v_it;
   v_it = v.begin();

   while (v_it != v.end())
   {
      aux.Insertar(aux.begin(),*v_it);
      ++v_it;
   }

   return aux;

}

int main(int argc, char const *argv[])
{

   if (argc != 4){
      cerr << "Error: Numero incorrecto de parametros.\n";
      cerr << "Uso: rebobinar <Prefijoentrada> <Fotogramas> <Prefijosalida> \n";
      exit (1);
   }

   int nf, nc, nframes;
   const char *origen, *destino;

   origen = argv[1];
   nframes = atoi(argv[2]);
   destino = argv[3];

   Video<unsigned char> vid(leeVideo(origen,nframes));

   Video<unsigned char> rebobinado(rebobinar(vid));

   //escribeImagen("100.pgm",vid[100]);

   escribeVideo(destino,rebobinado);

   return 0;
}