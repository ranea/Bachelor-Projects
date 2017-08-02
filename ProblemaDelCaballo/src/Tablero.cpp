/**
  * @file Tablero.cpp
  * @brief Implementacion de la clase Tablero 
  *
  * Permite representar el recorridos de un caballo
  * almacenando las casillas visitadas y la heuristica
  *
  */

#include "Tablero.h"
#include <iostream>

// Declaracion/inicializacion de las variables estaticas
const int Tablero::casillas_accesibilidad[DIM][DIM] =
{
	{2,3,4,4,4,4,3,2},
	{3,4,6,6,6,6,4,3},
	{4,6,8,8,8,8,6,4},
	{4,6,8,8,8,8,6,4},
	{4,6,8,8,8,8,6,4},
	{4,6,8,8,8,8,6,4},
	{3,4,6,6,6,6,4,3},
	{2,3,4,4,4,4,3,2}
};

/**
 * Constructor de la clase
 */
Tablero::Tablero(){
	accesibilidad_por_casillas = false;
	mirada_hacia_delante = false;
}


/**
 * Metodo para activar la heuristica de accesibilidad
 */
void Tablero::setHeuristicaAccesibilidad(){
   accesibilidad_por_casillas = true;
}


/**
 * Metodo para activar la heuristica de mirada hacia delante
 * y comprueba que la heuristica de accesibilidad este activada
 */
void Tablero::setHeuristicaMirada(){
	if(!accesibilidad_por_casillas){
		setHeuristicaAccesibilidad();
	}

   mirada_hacia_delante = true;
}