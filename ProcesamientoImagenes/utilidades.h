#ifndef _UTILIDADES_H_
#define _UTILIDADES_H_

#include "imagen.h"
#include "video.h"

/*
 * Almacena la imagen, guardada en el fichero "archivo", 
 * en un objeto del TDA imagen
 */
Imagen<unsigned char> leeImagen(const char * archivo);

/*
 * Escribe la imagen, guardada en el objeto del TDA imagen img,
 * en el fichero "archivo"
 */
void escribeImagen(const char * archivo, const Imagen<unsigned char>& img);

/*
 * Lee el video, guardado en disco como la secuencia de archivos
 *  "prefijo0001.pgm, prefijo0002.pgm, prefijo0003.pgm..." 
 * y lo almacena en un objeto del TDA video
 */
Video<unsigned char> leeVideo(const char* prefijo, int nframes);

/*
 * Escribe el video, guardado en el objeto del TDA Video V,
 * en la secuencia de archivos 
 *  "prefijo0001.pgm, prefijo0002.pgm, prefijo0003.pgm..." 
 */
void escribeVideo(const char * prefijo, const Video<unsigned char>& V);

#endif
