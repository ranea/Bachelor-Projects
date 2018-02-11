# Procesamiento de Imagenes
Algunas funciones simples de procesamientos de imágenes  y vídeos.

 - Umbralizar una imagen usando una escala de grises
 - Zoom de una porción de la imagen
 - Crear un icono a partir de una imagen
 - Aumento de contraste de una imagen
 - Rebobinar una video
 - Morphing.

## Umbralizar una imagen usando una escala de grises
Consiste en generar a partir de una imagen original, otra imagen con el criterio de que si un pixel de la imagen original tiene un nivel de gris p comprendido en un intervalo definido por 2 umbrales T1 y T2 , se deja con ese nivel de gris p y en otro caso, se pone a blanco (nivel de gris 255).

Los parámetros a la hora de ejecutarlo son:
 - **fichE**: nombre del fichero que contiene la imagen original.
 - **fichS**: nombre del fichero que contendrá el resultado de la transformación.
 - **T1 T2**: los valores del intervalo de la umbralización (T1 < T2 ).

## Zoom de una porción de la imagen
Consiste en realizar un zoom de una porción de la imagen mediante un simple procedimiento de interpolacıón consistente en construir a partir de una subimagen N × N , una imagen de dimension (2N − 1) × (2N − 1), poniendo entre cada 2 filas (resp. Columnas) de la imagen original otra fila (resp. columna) cuyos valores de gris son la media de los que tiene a la izquierda y a la derecha (resp. arriba y abajo).

Los parámetros a la hora de ejecutarlo son:
 - **fichE**: nombre del fichero que contiene la imagen original.
 - **fichS**: nombre del fichero que contedrá el resultado del zoom.
 - **x1 y1 x2 y2**: coordenadas de la esquina superior izquierda y esquina inferior derecha del trozo de imagen al que se le hará el zoom. Ha de ser un trozo cuadrado.

## Crear un icono a partir de una imagen
Consiste en crear una imagen de un tamaño muy reducido a partir de una imagen original. El algorítmo de reducción consiste básicamente tomar cada pixel de la salida como la media de los n × n píxeles de la entrada si se quiere hacer una reducción de nx.

Los parámetros a la hora de ejecutarlo son:
 - **fich_orig**: nombre del fichero que contiene la imagen original.
 - **fich_rdo**: nombre del fichero donde se guardará el icono.
 - **nf nc**: número de filas y columnas del icono resultante.

## Aumento de contraste de una imagen
Aumentar el contraste en una imagen consiste en generar una imagen de niveles de gris con más contraste que la original. Supongamos que el rango de niveles de gris de la imagen es [a, b], o sea, el mínimo nivel de gris de la imagen es a y el máximo es b. Vamos a modificar dicho intervalo en [min,max] mediante una transformación lineal.

Los parámetros a la hora de ejecutarlo son:
 - **fichE**: nombre del fichero que contiene la imagen fuente.
 - **fichS**: nombre del fichero que contedr´a el resultado.
 - **min max**: los extremos del nuevo rango de la imagen (los valores de los extremos del intervalo de niveles de gris para la imagen resultante)

## Rebobinar una video
Vamos a generar una función que a partir de un vídeo obtenga el vídeo invertido.

Los parámetros a la hora de ejecutarlo son:
 - prefijo del nombre de las imágenes que forman el vídeo de entrada
 - número de fotogramas del vídeo de entrada
 - prefijo del nombre de las imágenes que forman el vídeo de salida

## Morphing.
El morphing se usa para cambiar una imagen en otra o para proporcionar una transición suave
de una imagen a otra creando la ilusión de una transformación.

Los parámetros a la hora de ejecutarlo son:
 - **fich_orig**: es el nombre del fichero que contiene la imagen inicial de la que se parte
 - **fich_rdo**: es el nombre del fichero que contiene la imagen final a la que se pretende llegar
 - Número de pasos para realizar la transformación
 - Prefijo de las imágenes que forman el vídeo de salida.
