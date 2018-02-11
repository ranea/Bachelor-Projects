/**
  * @file video.h
  * @Implementacion del TDA vídeo con template
  */

#ifndef __VIDEO__H_
#define __VIDEO__H_

#include "imagen.h"
#include <list>

/**
 *  @brief T.D.A. Vídeo
 *
 *
 * Una instancia @e V del tipo de dato abstracto Vídeo sobre un dominio @e T es
 * una conjunto de datos del tipo \c Imagen<T>. Lo podemos contemplar como un vector 
 * de @e n fotogramas (imagenes digitales que han sucedido a lo largo de un espacio
 * temporal de una escena).
 * 
 * En un vídeo, cada elemento V(t), con 0<=t<n, almacena una imagen digital 
 * asociada al instante t.
 *
 * Para poder usar el tipo de dato Video se debe incluir el fichero
 * 
 *   <tt>\#include vídeo.h</tt>
 *
 * @authors Antonio Álvarez y Adrián
 * @date Enero 2013
*/

template <class T>
class Video{
private:
   std::list< Imagen<T> > lista_frames; /**< Almacena los fotogramas */
   int nframes;      /**< Número de imágenes almacenadas en \c V */

public:
   // ---------------  Constructores ----------------
   /**
    * @brief Constructor por defecto.
    */
   Video();

   /**
    * @brief Constructor de copia.
    * @param V Vídeo a copiar.
    */
   Video(const Video<T>& V);

   /**
    * @brief Operador de asignación.
    * @param V El vídeo a asignar.
    * @return Una referencia al vídeo asignado.
    */
   Video<T> & operator=(const Video<T> &V);


   // ---------------  Destructores ----------------
   /**
    * @brief Destructor.
    *
    * Libera los recursos ocupados por el vídeo.
    * El objeto no es reutilizable.
    */
   ~Video();


   // --------------- Otras funciones ---------------
   /**
    * @brief Numero de fotogramas del vídeo.
    * @return Devuelve el numero de frames del vídeo. 
    */
   int num_fotogramas() const;

   /**
    * @brief Acceso al fotograma i-ésimo.
    * @param i fotograma i-esimo consultar.
    * @pre 0<=i<V.num_fotogramas().
    * @return Devuelve una referencia al fotograma i-ésimo.
    *
    * @note La eficiencia es O(n). Se recomienda usar los iteradores.
    */
   Imagen<T>& operator[](int i);

   /**
    * @brief Acceso solo lectura al fotograma i-ésimo.
    * @param i fotograma i-esimo consultar.
    * @pre 0<=i<V.num_fotogramas().
    * @return Devuelve una referencia constante al fotograma i-ésimo.
    *
    * @note La eficiencia es O(n). Se recomienda usar los iteradores.
    */
   const Imagen<T>& operator[](int i) const;


   // ----------------- Iteradores ---------------
   /**
    * @brief Iterador a un fotograma del vídeo.
    */
   class iterator{
      private:
         typename std::list< Imagen<T> >::iterator lista_it; /**< Iterador a los fotogramas. */
      public:
         // ---------------  Constructores ----------------
         /**
          * @brief Constructor por defecto.
          */
         iterator();
         /**
          * @brief Constructor de copia.
          * @param it iterador a copiar.
          */
         iterator(const iterator& it);
          

         // --------------- Operadores ---------------
         /**
          * @brief Operador siguiente.
          * @return Devuelve el siguiente elemento al que estaba referenciado.
          */
         iterator & operator++();

         /**
          * @brief Operador anterior.
          * @return Devuelve el elemento anterior al que estaba referenciado.
          */
         iterator & operator--();

         /**
          * @brief Operador de igualdad.
          * @param it iterador que se quiere comparar.
          * @return Devuelve @e true si ambos elementos apuntados son iguales,
          * en caso contrario devuelve @e false.
          */
         bool operator==(const iterator& it) const;

         /**
          * @brief Operador de no igualdad.
          * @param it iterador que se quiere comparar.
          * @return Devuelve @e true si ambos elementos apuntados son diferentes,
          * en caso contrario devuelve @e false.
          */
         bool operator!=(const iterator& it) const;

         /**
         * @brief Operador de indirección.
         * @return Devuelve el objeto referenciado por el iterador.
         */
         Imagen<T>& operator*();

         friend class Video;
   };

   /**
    * @brief Iterador constante a un fotograma del vídeo.
    */
   class const_iterator{
      private:
         typename std::list< Imagen<T> >::const_iterator lista_it; /**< Iterador a los fotogramas. */
      public:
         // ---------------  Constructores ----------------
         /**
          * @brief Constructor por defecto.
          */
         const_iterator();
         /**
          * @brief Constructor de copia.
          * @param it Iterador a copiar.
          */
         const_iterator(const const_iterator& it);
          
         // --------------- Operadores ---------------
         /**
          * @brief Operador siguiente.
          * @return Devuelve el siguiente elemento al que estaba referenciado.
          */
         const_iterator& operator++();

         /**
          * @brief Operador anterior.
          * @return Devuelve el elemento anterior al que estaba referenciado.
          */
         const_iterator& operator--();

         /**
          * @brief Operador de igualdad.
          * @param it iterador que se quiere comparar.
          * @return Devuelve @e true si ambos elementos apuntados son iguales,
          * en caso contrario devuelve @e false.
          */
         bool operator==(const const_iterator& it) const;

         /**
          * @brief Operador de no igualdad.
          * @param it iterador que se quiere comparar.
          * @return Devuelve @e true si ambos elementos apuntados son diferentes,
          * en caso contrario devuelve @e false.
          */
         bool operator!=(const const_iterator& it) const;

         /**
         * @brief Operador de indireccion.
         * @return Devuelve el objeto referenciado por el iterador.
         */
         const Imagen<T>& operator*() const;

         friend class Video;
   };

   /**
    * @brief Inserta en la posicion del iterador el nuevo fotograma.
    * @param it iterador a la posicion a insertar el fotograma.
    * @pre it debe apuntar a una posicion valida dentro del vídeo.
    * @param I imagen a insertar.
    * @return Devuelve un iterador que apunta al nuevo fotograma .
    *
    * @note El tamaño del vídeo aumenta en 1.
    */
   iterator Insertar(iterator it, const Imagen<T> &I);

   /**
    * @brief Borra el fotograma dado por el iterador.
    * @param it iterador al fotograma a borrar.
    * @pre it debe apuntar a una posición válida dentro del vídeo.
    * @return Devuelve un iterador que apunta al lugar del fotograma borrado. 
    * 
    * @note El tamaño del vídeo decrementa en 1.
    */
   iterator Borrar(iterator it);


   /**
    * @brief Iterador al primer fotograma.
    * @return Devuelve un iterador apuntando al primer fotograma.
    */
   iterator begin();

   /**
    * @brief Iterador constante al primer fotograma.
    * @return Devuelve un iterador constante apuntando al primer fotograma.
    */
   const_iterator begin() const;

   /**
    * @brief Iterador al ultimo fotograma.
    * @return Devuelve un iterador apuntando al ultimo fotograma.
    */
   iterator end();

   /**
    * @brief Iterador constante al ultimo fotograma.
    * @return Devuelve un iterador constante apuntando al ultimo fotograma.
    */
   const_iterator end() const;
};

#include "video.cpp"
#endif