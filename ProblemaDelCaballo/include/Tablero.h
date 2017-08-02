/**
  * @file Tablero.h
  * @brief Cabecera de la clase Tablero 
  *
  * Permite representar el recorridos de un caballo
  * almacenando las casillas visitadas y la heuristica
  *
  */
 
#ifndef TABLERO
#define TABLERO

/**
 * Clase Tablero
 */
class Tablero{
private:
   /**
    * Dimension del tablero. 
    */
   static const int DIM = 8;

   /**
    * Matriz que muestra si la casilla se ha visitado (1)
    * o no se ha visitado (0)
    */
   int casillas_visitadas[DIM][DIM];

   /**
    * Matriz que muestra la heuristica de accesibilidad:
    * en cada casilla se escribe desde cuantas posiciones
    * se puede llegar hasta ella
    */
   static const int casillas_accesibilidad[DIM][DIM];

   /**
    * Activa o desactiva la heuristica de accesibilidad:
    * elegir primero las casillas mas inaccesibles
    */
   bool accesibilidad_por_casillas;

   /**
    * Activa o desactiva la heuristica de mirada hacia delante:
    * deshacer el empate para casillas con la misma inaccesibilidad
    */
   bool mirada_hacia_delante;

public:
   /**
    * Constructor de la clase
    */
   Tablero();

   /**
    * Metodo para activar la heuristica de accesibilidad
    */
   void setHeuristicaAccesibilidad();

   /**
    * Metodo para activar la heuristica de mirada hacia delante
    * y comprueba que la heuristica de accesibilidad este activada
    */
   void setHeuristicaMirada();

   friend class Caballo;
};

#endif


/* Fin Fichero: Tablero.h */