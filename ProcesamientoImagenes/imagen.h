/**
* @file imagen.h
* @brief Implementacion del TDA imagen con template
*/
#ifndef __IMAGEN_H_
#define __IMAGEN_H_

/**
 *  @brief T.D.A. Imagen
 *
 *
 * Una instancia @e I del tipo de dato abstracto Imagen sobre un dominio @e T es
 * un conjunto de datos del tipo \c \<T\>. Lo podemos contemplar como un puntero 
 * a un array de punteros que llegan a un array de 1D, formando una matriz de 2D. 
 * 
 * En una imagen, cada elemento I(x,y) es un píxel en la posición (x,y) que 
 * contiene uno o más valores de color para codificar la imagen.
 *
 * Para poder usar el tipo de dato Imagen se debe incluir el fichero
 * 
 *   <tt>\#include imagen.h</tt>
 *
 * @authors Adrián y Antonio Álvarez
 * @date Enero 2013
*/
template <class T>
class Imagen 
{
private:

   /**
   * @brief El número de filas de la imagen.
   */

   int filas; 

   /**
   * @brief El número de columnas de la imagen.
   */

   int cols;

   /**
   * @brief La imagen como una matriz dinámica de tipo T.
   */

   T** img;

public:
   // ----------------- Constructores -----------------
   /** 
   * @brief Constructor por defecto de imagen.
   */

   Imagen();   

   /**
   * @brief Constructor con parámetros de imagen.
   * @param filas El número de filas de la nueva imagen.
   * @param columnas El número de columnas de la nueva imagen.
   */

   Imagen(int filas, int columnas);

   /**
   * @brief Constructor de copia de imagen.
   * @param orig Imagen original a copiar.
   */

   Imagen(const Imagen &orig);

   /**
   * @brief Destructor de Imagen.
   */

   ~Imagen();

   /**
   * @brief Número de filas de la imagen pasada como parámetro.
   * @return El número de filas de la imagen.
   */

   // -------------------- Operadores -----------------------

   int num_filas() const;

   /**
   * @brief Número de columnas de la imagen pasada como parámetro.
   * @return El número de columnas de la imagen.
   */

   int num_columnas() const;

   /**
   * @brief Valor del píxel pasado como argumento.
   * @param fila La fila del píxel a consultar.
   * @param col La columna del píxel a consultar.
   * @return Referencia del píxel deseado.
   */

   T & operator()(int fila, int col);

   /**
   * @brief Valor del píxel pasado como argumento.
   * @param fila La fila del píxel a consultar.
   * @param col La columna del píxel a consultar.
   * @return Referencia constante del píxel deseado.
   */

   const T & operator()(int fila, int col) const;

   /**
   * @brief Operador de asignación de Imagen.
   * @param orig La imagen a asignar
   * @return Una referencia a la imagen asignada.
   */

   Imagen<T>& operator=(const Imagen<T> &orig);

   /**
   * @brief Comprueba si la imagen es vacía.
   * @return Si la imagen es vacía o no.
   */

   bool es_vacia() const;

   /**
   * @brief Rellenar una imagen con el contenido de un array.
   * @param array El array de donde sacar los datos.
   * @pre El array debe contener al menos filas*cols elementos.
   */

   void rellena(const T* array);

   /**
   * @brief Imprimir una imagen en un array.
   * @param array El array donde imprimir los datos.
   * @pre El array debe tener reservado al menos filas*cols elementos.
   */

   void imprime(T* array) const;

// ----------------- Iteradores ---------------

   /**
   * @brief Iterador a una fila de la imagen.
   */
   class iterator_fila{
      private:
         T* puntero; /**< Puntero a una fila de la imagen. */
         int filas; /**< Numero de filas de la imagen. */
         int cols; /**< Numero de columnas de la imagen. */
      public:

         // --------- Constructores ------------
         
         /**
         * @brief Constructor por defecto .
         */

         iterator_fila(int filas=0, int cols=0);

         /**
         * @brief Constructor de copia.
         * @param it Iterador a copiar.
         */

         iterator_fila(const iterator_fila &it);

         // ----------- Operadores --------

         /**
          * @brief Operador de asignación.
          * @return Devuelve una referencia al iterador asignado.
          */

         iterator_fila& operator= (const iterator_fila& orig);

         /**
         * @brief Operador de indireccion.
         * @return Devuelve el objeto referenciado por el iterador.
         */

         T& operator*() const;

         /**
          * @brief Operador siguiente.
          * @return Devuelve el siguiente elemento al que estaba referenciado.
          */         

         iterator_fila& operator++();

         /**
          * @brief Operador anterior.
          * @return Devuelve el elemento anterior al que estaba referenciado.
          */         

         iterator_fila& operator--();

         /**
          * @brief Operador de no igualdad.
          * @param it iterador que se quiere comparar.
          * @return Devuelve true si ambos elementos apuntados son diferentes,
          * en caso contrario devuelve false.
          */

         bool operator!=(const iterator_fila& it) const;

         /**
          * @brief Operador de igualdad.
          * @param it iterador que se quiere comparar.
          * @return Devuelve true si ambos elementos apuntados son iguales,
          * en caso contrario devuelve false.
          */

         bool operator==(const iterator_fila& it) const;

         /**
         * @brief Iterador a una columna de la imagen.
         */
         class iterator_columna{
            private:
               T* puntero; /**< Puntero a una columna de la imagen. */
            public:
               // --------- Constructores ------------
               
               /**
               * @brief Constructor por defecto. 
               */

               iterator_columna();

               /**
               * @brief Constructor de copia.
               * @param it iterador a copiar.
               */

               iterator_columna(const iterator_columna &it);

               // ----------- Operadores --------

               /**
                * @brief Operador de asignación.
                * @return Devuelve una referencia al iterador asignado.
                */

               iterator_columna& operator= (const iterator_columna& orig);

               /**
               * @brief Operador de indireccion.
               * @return Devuelve el objeto referenciado por el iterador.
               */

               T& operator*() const;

               /**
                * @brief Operador siguiente.
                * @return Devuelve el siguiente elemento al que estaba referenciado.
                */         

               iterator_columna& operator++();

               /**
                * @brief Operador anterior.
                * @return Devuelve el elemento anterior al que estaba referenciado.
                */         

               iterator_columna& operator--();

               /**
                * @brief Operador de no igualdad.
                * @param it iterador que se quiere comparar.
                * @return Devuelve true si ambos elementos apuntados son diferentes,
                * en caso contrario devuelve false.
                */

               bool operator!=(const iterator_columna& it) const;

               /**
                * @brief Operador de igualdad.
                * @param it iterador que se quiere comparar.
                * @return Devuelve true si ambos elementos apuntados son iguales,
                * en caso contrario devuelve false.
                */

               bool operator==(const iterator_columna& it) const;

               friend class iterator_fila;
         };

         /**
          * @brief Iterador a la primera fila.
          * @return Un iterador a la primera fila de la imagen.
          */

         iterator_columna begin();
         
         /**
          * @brief Iterador a la primera fila.
          * @return Un iterador a la primera fila de la imagen.
          */

         iterator_columna end();

         friend class Imagen;
   };

   /**
   * @brief Iterador constante a una fila de la imagen.
   */
   class const_iterator_fila{
      private:
         const T* puntero; /**< Puntero a una fila. */
         int filas; /**< Numero de filas de la imagen. */
         int cols; /**< Numero de columnas de la imagen. */
      public:
         // ---------------  Constructores ----------------
         
         /**
          * @brief Constructor por defecto.
          */

         const_iterator_fila(int filas=0, int cols=0);

         /**
          * @brief Constructor de copia.
          * @param it iterador a copiar.
          */         

         const_iterator_fila(const const_iterator_fila &it);

         // ----------- Operadores --------

         /**
          * @brief Operador de asignación.
          * @return Devuelve una referencia al iterador asignado.
          */

         const_iterator_fila& operator= (const const_iterator_fila& orig);

         /**
         * @brief Operador de indireccion.
         * @return Devuelve el objeto referenciado por el iterador.
         */         

         const T& operator*() const;

         /**
          * @brief Operador siguiente.
          * @return Devuelve el siguiente elemento al que estaba referenciado.
          */      

         const_iterator_fila& operator++();

         /**
          * @brief Operador anterior.
          * @return Devuelve el elemento anterior al que estaba referenciado.
          */         

         const_iterator_fila& operator--();

         /**
          * @brief Operador de no igualdad.
          * @param it iterador que se quiere comparar.
          * @return Devulve true si ambos elementos apuntados son diferentes,
          * en caso contrario devuelve false.
          */

         bool operator!=(const const_iterator_fila& it) const;

         /**
          * @brief Operador de igualdad.
          * @param it iterador que se quiere comparar.
          * @return Devulve true si ambos elementos apuntados son iguales,
          * en caso contrario devuelve false.
          */         

         bool operator==(const const_iterator_fila& it) const;

         /**
         * @brief Iterador constante a una columna de la imagen.
         */
         class const_iterator_columna{
            private:
               const T* puntero; /**< Puntero a una columna de la imagen */
            public:
               // --------- Constructores ------------
               
               /**
               * @brief Constructor por defecto. 
               */

               const_iterator_columna();

               /**
               * @brief Constructor de copia.
               * @param it iterador a copiar.
               */

               const_iterator_columna(const const_iterator_columna &it);

               // ----------- Operadores --------

               /**
                * @brief Operador de asignación.
                * @return Devuelve una referencia al iterador asignado.
                */

               const_iterator_columna& operator= (const const_iterator_columna& orig);

               /**
               * @brief Operador de indireccion.
               * @return Devuelve el objeto referenciado por el iterador.
               */

               const T& operator*() const;

               /**
                * @brief Operador siguiente.
                * @return Devuelve el siguiente elemento al que estaba referenciado.
                */         

               const_iterator_columna& operator++();

               /**
                * @brief Operador anterior.
                * @return Devuelve el elemento anterior al que estaba referenciado.
                */         

               const_iterator_columna& operator--();

               /**
                * @brief Operador de no igualdad.
                * @param it iterador que se quiere comparar.
                * @return Devulve true si ambos elementos apuntados son diferentes,
                * en caso contrario devuelve false.
                */

               bool operator!=(const const_iterator_columna& it) const;

               /**
                * @brief Operador de igualdad.
                * @param it iterador que se quiere comparar.
                * @return Devulve true si ambos elementos apuntados son iguales,
                * en caso contrario devuelve false.
                */

               bool operator==(const const_iterator_columna& it) const;

               friend class const_iterator_fila;
         };

         /**
          * @brief Iterador a la primera fila.
          * @return Un iterador a la primera fila de la imagen.
          */

         const_iterator_columna begin() const;
         
         /**
          * @brief Iterador a la primera fila.
          * @return Un iterador a la primera fila de la imagen.
          */
          
         const_iterator_columna end() const;

         friend class Imagen;

   };

   /**
   * @brief Iterador a la primera fila.
   * @return Un iterador a la primera fila de la imagen.
   */

   iterator_fila begin();

   /**
   * @brief Iterador constante a la primera fila.
   * @return Un iterador constante a la primera fila de la imagen.
   */

   const_iterator_fila begin() const;

   /**
   * @brief Iterador a la última fila.
   * @return Un iterador a la última fila de la imagen.
   */

   iterator_fila end();

   /**
   * @brief Iterador constante a la última fila.
   * @return Un iterador constante a la última fila de la imagen.
   */

   const_iterator_fila end() const;
};

#include "imagen.cpp"
#endif