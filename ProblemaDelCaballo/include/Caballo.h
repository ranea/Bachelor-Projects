/**
  * @file Caballo.h
  * @brief Cabecera de la clase Caballo 
  *
  * Permite representar los movimientos y 
  * recorridos completos de un caballo
  * por un tablero de ajedrez
  */

#ifndef CABALLO
#define CABALLO
#include "Tablero.h"

/**
 * Clase Caballo
 */
class Caballo{

private:
   /**
    * Vector con los posibles movimientos horizontales
    */
   static const int mov_col[8];

   /**
    * Vector con los posibles movimientos verticales
    */
   static const int mov_fila[8];

   /**
    * Puntero a la casillas visitadas del tablero y a la heuristica
    */
   Tablero * tab;

   /**
    * Contador con el numero de desplazamientos del caballo
    */
   int num_mov;

   /**
    * Fila donde se encuentra el caballo
    */
   int fila_actual;

   /**
    * Columna donde se encuentra el caballo
    */
   int col_actual;

   /**
    * Metodo para eligir el salto del caballo dependendiendo
    * de la accesibilidad de las casillas. 
    * NOTA: si esta desactivada la heuristica de mirada hacia
    * delante se deshace el empate de forma aleatori.
    * @param indices_mov[] array con los indices de los movimientos validos
    * @param num_mov_validos contador con el numero de indices validos
    * @return indice del salto elegido
   */
   int eligeMov(int indices_mov[], int num_mov_validos);


   /**
    * Metodo para determinar si el mov[i] es posible 
    * @param i indice del movimiento
    * @return exito o fracaso del posible salto
    */
   bool movPosible(int i);

   /**
    * Metodo para calcular la casilla con menor accesibilidad
    * desde una fila y columna cualquiera
    * @param fila fila desde donde se calcula la accesibilidad
    * @param col columna desde donde se calcula la accesibilidad
    * @return minima accesibilidad
    */
   int calculaMinimiAccesibilidad(int fila, int col);

public:
   /**
    * Constructor de la clase. Se inicializa la semilla
    * de rand() con la hora del sistema para generar
    * numeros aleatorios.
    * @param fila_inicial  fila inicial donde se situara el caballo
    * @param col_inicial columna inicial donde se situara el caballo
    * @param &tablero objeto de la clase tablero
    */
   Caballo(int fila_inicial, int col_inicial, Tablero &tablero);

   /**
    * Metodo para establecer la posicion inicial del caballo,
    * resetear la matriz de casillas visitas y reinicia
    * el contador de movimientos a cero
    * @param fila_inicial fila inicial donde se situara el caballo
    * @param col_inicial columna inicial donde se situara el caballo
    */
   void reset(int fila_inicial, int col_inicial);

   /**
    * Metodo para desplazar el caballo un salto
    * @return exito o fracaso del salto
    */
   bool salto();

   /**
    * Metodo para realizar un recorrido completo
    * por todas las casillas pasando una sola vez
    * @return numero de movientos realizados
    */
   int recorridoCompleto();

   /**
    * Metodo que averigua el numero de recorridos exitosos
    * y la media de los movimientos realizados en un numero de intentos 
    * @param intentos numero de intentos a provar
    * @param &exitos numero de exitos conseguidos, devuelto por referencia
    * @param media_mov media de los desplazamientosa, devuelto por referencia
    */
   void recorridosExitosos(int intentos, int &exitos, int &media_mov);

   /**
    * Metodo que imprime el tablero mostrando 
    * las casillas por donde ha pasado el caballo
    */
   void imprimeCasillasVisitadas();
};

#endif


/* Fin Fichero: Caballo.h */