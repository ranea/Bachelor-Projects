/**
  * @file Caballo.cpp
  * @brief Implementacion de la clase Caballo 
  *
  * Permite representar los movimientos y 
  * recorridos completos de un caballo
  * por un tablero de ajedrez
  */

#include "Caballo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

// Declaracion/inicializacion de las variables estaticas
const int Caballo::mov_fila[8] = {-1,-2,-2,-1,1,2,2,1};
const int Caballo::mov_col[8] = {2,1,-1,-2,-2,-1,1,2};


/**
 * Constructor de la clase. Se inicializa la semilla
 * de rand() con la hora del sistema para generar
 * numeros aleatorios.
 * @param fila_inicial  fila inicial donde se situara el caballo
 * @param col_inicial columna inicial donde se situara el caballo
 * @param &tablero objeto de la clase tablero
 */
Caballo::Caballo(int fila_inicial, int col_inicial, Tablero &tablero)
{
	tab = &tablero;	

	reset(fila_inicial,col_inicial);

   time_t t;
   srand ((int) time(&t));
}

/**
 * Metodo para establecer la posicion inicial del caballo,
 * resetear la matriz de casillas visitas y reinicia
 * el contador de movimientos a cero
 * @param fila_inicial fila inicial donde se situara el caballo
 * @param col_inicial columna inicial donde se situara el caballo
 */
void Caballo::reset(int fila_inicial, int col_inicial)
{
   num_mov = 0;

   fila_actual = fila_inicial;
   col_actual = col_inicial;

   for (int i = 0; i < tab->DIM; ++i)
   {
   	for (int j = 0; j < tab->DIM; ++j)
   	{
   		tab->casillas_visitadas[i][j]=0;
   	}
   }
}

/**
 * Metodo para desplazar el caballo un salto
 * @return exito o fracaso del salto
 */
bool Caballo::salto()
{
   /**
    * Almacenamos en un array los indices de los movimientos validos
    * y elegimos uno de esos indices segun la heuristica
    */
      
	bool salto_valido = true;
	int indices_mov[tab->DIM];
	int num_mov_validos = 0;

	for (int i = 0; i < tab->DIM; ++i)
	{
		if (movPosible(i)){
			indices_mov[num_mov_validos] = i;
			num_mov_validos++;
		}
	} 

	if (num_mov_validos == 0)
   {
		salto_valido = false;
	}
	else
   {
      int mov_valido;

      if (tab->accesibilidad_por_casillas)
      {
         mov_valido = eligeMov(indices_mov,num_mov_validos);
      }
      else
      {
         mov_valido = indices_mov[rand() % num_mov_validos]; 
      }

		tab->casillas_visitadas[fila_actual][col_actual] = 1;
		fila_actual += mov_fila[mov_valido];
		col_actual += mov_col[mov_valido];

		num_mov++;
	}

	return salto_valido;
}

/**
 * Metodo para eligir el salto del caballo dependendiendo
 * de la accesibilidad de las casillas. 
 * NOTA: si esta desactivada la heuristica de mirada hacia
 * delante se deshace el empate de forma aleatori.
 * @param indices_mov[] array con los indices de los movimientos validos
 * @param num_mov_validos contador con el numero de indices validos
 * @return indice del salto elegido
 */
int Caballo::eligeMov(int indices_mov[], int num_mov_validos)
{
      int mov_valido = indices_mov[0];
      int nueva_fila = fila_actual + mov_fila[mov_valido];
      int nueva_col = col_actual + mov_col[mov_valido];
      int accesibilidad = tab->casillas_accesibilidad[nueva_fila][nueva_col];

      for (int i = 1; i < num_mov_validos; ++i)
      {
         int posible_nueva_fila = fila_actual + mov_fila[indices_mov[i]];
         int posible_nueva_col = col_actual + mov_col[indices_mov[i]]; 
         int nueva_accesibilidad = tab->casillas_accesibilidad[posible_nueva_fila][posible_nueva_col];
         bool salto_nuevo_valido = false; 

         if (accesibilidad == nueva_accesibilidad)
         {

            if(tab->mirada_hacia_delante)
            {
               int acces_nueva = calculaMinimiAccesibilidad(posible_nueva_fila,posible_nueva_col);
               int acces_vieja = calculaMinimiAccesibilidad(nueva_fila,nueva_col);

               if (acces_nueva < acces_vieja)
               {
                  salto_nuevo_valido = true;
               }
               else if (acces_nueva == acces_vieja)
               {
                  salto_nuevo_valido = rand() % 2;
               }
            }

            else
            {
               salto_nuevo_valido = rand() % 2;
            }
         }

         if (nueva_accesibilidad < accesibilidad || salto_nuevo_valido)
         {
            accesibilidad = nueva_accesibilidad;
            nueva_fila = posible_nueva_fila;
            nueva_col = posible_nueva_col;
            mov_valido = indices_mov[i];
         }
      }

      return mov_valido;
}

/**
 * Metodo para calcular la casilla con menor accesibilidad
 * desde una fila y columna cualquiera
 * @param fila fila desde donde se calcula la accesibilidad
 * @param col columna desde donde se calcula la accesibilidad
 * @return minima accesibilidad
 */
int Caballo::calculaMinimiAccesibilidad(int fila, int col)
{
   /* 1º Almacenamos la posicion del caballo antes de saltar 
    *    a la casilla desde donde queremos calcular la accesibildad
    * 2º Calculamos los indices de movimientos posibles de dicha casilla
    * 3º Elegimos aquel movimiento que tenga menor accesibilidad.
    *    (si al comparar dos movimientos tienen la misma, deshacemos
    *    el empate de forma aleatoria)
    */

   int fila_actual_guardada = fila_actual;
   int col_actual_guardada = col_actual;

   fila_actual = fila;
   col_actual = col;

   int indices_mov[tab->DIM];
   int num_mov_validos = 0;

   for (int i = 0; i < tab->DIM; ++i)
   {
      if (movPosible(i)){
         indices_mov[num_mov_validos] = i;
         num_mov_validos++;
      }
   } 

   int nueva_fila = fila_actual + mov_fila[indices_mov[0]];
   int nueva_col = col_actual + mov_col[indices_mov[0]];
   int menor_accesibilidad = tab->casillas_accesibilidad[nueva_fila][nueva_col];

   for (int i = 1; i < num_mov_validos; ++i)
   {
      nueva_fila = fila_actual + mov_fila[indices_mov[i]];
      nueva_col = col_actual + mov_col[indices_mov[i]]; 
      int nueva_accesibilidad = tab->casillas_accesibilidad[nueva_fila][nueva_col];
      bool nueva_access_valida = false;

      if (nueva_accesibilidad == menor_accesibilidad)
      {
         nueva_access_valida = (int)(2.0*rand()/(RAND_MAX+1.0));
      }
      else if (nueva_accesibilidad < menor_accesibilidad || nueva_access_valida)
      {
         menor_accesibilidad = nueva_accesibilidad;
      }
   }

   fila_actual = fila_actual_guardada;
   col_actual = col_actual_guardada;

   return menor_accesibilidad;
}

/**
 * Metodo para determinar si el mov[i] es posible 
 * @param i indice del movimiento
 * @return exito o fracaso del posible salto
 */
bool Caballo::movPosible(int i)
{
	bool mov_posible = false;

   int nueva_fila = fila_actual + mov_fila[i];
	int nueva_col = col_actual + mov_col[i]; 

	if (nueva_col>=0 && nueva_col<=7 && nueva_fila>=0  && nueva_fila<=7
		&& tab->casillas_visitadas[nueva_fila][nueva_col]==0)
   {
      mov_posible = true;
   }
		
	return mov_posible;
}

/**
 * Metodo para realizar un recorrido completo
 * por todas las casillas pasando una sola vez
 * @return numero de movientos realizados
 */
int Caballo::recorridoCompleto()
{
	int movimientos = 0;

	while (salto() && movimientos<64)
   {
		movimientos++;
	}

	return movimientos;
}

/**
 * Metodo que averigua el numero de recorridos exitosos
 * y la media de los movimientos realizados en un numero de intentos 
 * @param intentos numero de intentos a provar
 * @param &exitos numero de exitos conseguidos, devuelto por referencia
 * @param media_mov media de los desplazamientosa, devuelto por referencia
 */
void Caballo::recorridosExitosos(int intentos, int &exitos, int &media_mov)
{
   exitos = 0;
   media_mov = 0;

   int fila_inicial = fila_actual;
   int col_inicial = col_actual;

   for (int i = 0; i < intentos; ++i)
   {   	
      reset(fila_inicial,col_inicial);
      int mov_realizados = recorridoCompleto();

      if (mov_realizados == 63)
      {
         exitos++;
      }
         
      media_mov += mov_realizados;
   }

   media_mov = media_mov/intentos;
}

/**
 * Metodo que imprime el tablero mostrando 
 * las casillas por donde ha pasado el caballo
*/
void Caballo::imprimeCasillasVisitadas()
{
   cout << " ·) Posicion final del caballo: (" << fila_actual << "," << col_actual << ")" << endl;
   cout << endl;

	for (int i = 0; i < tab->DIM; ++i)
	{
		cout << "  ( ";
		for (int j = 0; j < tab->DIM; ++j)
		{
			if (i==fila_actual && j==col_actual)
				cout << "  ";
			else
				cout << tab->casillas_visitadas[i][j] << " " ;
		}
		cout << ")" << endl;
	}

   cout << endl;
}