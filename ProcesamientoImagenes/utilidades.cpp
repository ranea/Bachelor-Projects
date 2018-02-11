#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "imagen.h"
#include "video.h"
#include "imagenES.h"
#include "utilidades.h"

using namespace std;

/* ___________________________________________________________________ */

Imagen<unsigned char> leeImagen(const char * archivo)
{
   unsigned char * buffer;
   int nf, nc;

   // Almacenamos en un buffer temporal la imagen archivo
   buffer = (LeerImagenPGM (archivo, nf, nc));

   // Almacenamos la imagen en un objeto del TDA imagen
   Imagen<unsigned char> img(nf,nc);
   img.rellena(buffer);

   if (img.es_vacia()){
      cerr << "Error: No pudo leerse la imagen." << endl;
      cerr << "Terminando la ejecucion del programa." << endl;
      exit (1);
   }

   cout << "Dimensiones de " << archivo << ":" << endl;
   cout << "   Imagen   = " << nf  << " filas x " << nc << " columnas " << endl;     

   delete[] buffer;
   return img;
}


/* ___________________________________________________________________ */

void escribeImagen(const char * archivo, const Imagen<unsigned char>& img)
{
   unsigned char * buffer;
   int nf, nc;

   nf = img.num_filas();
   nc = img.num_columnas();

   // Reservamos espacio para el contenido de la imagen
   buffer = new unsigned char[nf*nc + 1];
   buffer[nf*nc] = '\0';
   
   // Almacenamos el contenido la imagen en el buffer
   img.imprime(buffer);

   if (EscribirImagenPGM (archivo, buffer, nf, nc))
      cout  << "La imagen se guardo en " << archivo << endl;
   else{
      cerr << "Error: No pudo guardarse la imagen." << endl;
      cerr << "Terminando la ejecucion del programa." << endl;
      exit (2);
   }

   delete[] buffer;
}


/* ___________________________________________________________________ */

Video<unsigned char> leeVideo(const char* prefijo, int nframes)
{
   Video<unsigned char> vid;
   Imagen<unsigned char> img;

   for (int i = 0; i < nframes; i++)
   {
      char *archivo = new char [strlen(prefijo) + 10];
      sprintf (archivo,"%s%04d.pgm",prefijo,i);
      printf("Leyendo imagen %s...\n", archivo);
      img = leeImagen(archivo);
      printf("Imagen %s leída, insertando en vídeo\n", archivo);
      cout << endl;
      vid.Insertar(vid.end(),img);
   }

   return vid;
}


/* ___________________________________________________________________ */

void escribeVideo(const char * prefijo, const Video<unsigned char>& V)
{
   Video<unsigned char>::const_iterator it = V.begin();

   char * archivo = new char[strlen(prefijo)+4*sizeof(char)];
   
   int i = 0;
   for (it; it != V.end(); ++it,++i)
   {
      // Usamos sprintf para crear los nombres de los fotogramas
      sprintf (archivo,"%s%04d.pgm",prefijo,i);
      escribeImagen(archivo,*it);
   }
}