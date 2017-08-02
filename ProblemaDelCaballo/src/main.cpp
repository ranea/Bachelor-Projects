#include <iostream>
#include <stdlib.h>
#include "Caballo.h"
using namespace std;

void eligePosInicial(int &fila_inicial, int &col_inicial);
void eligeHeuristica(int &opcion);
void imprimeDato(int &fila,int &col,int &exitos,int &media,int &i);

int main(){
   cout << "~~ Programa que comprueba si dada una posicion y una heuristica" << endl;
   cout << "~~ un caballo recorrería un tablero de ajedrez sin repetir casillas " << endl;
      
   int fila_inicial, col_inicial;
   eligePosInicial(fila_inicial,col_inicial);

   int opcion;
   eligeHeuristica(opcion);

   Tablero tablero;
   switch(opcion)
   {
      case 2: 
         tablero.setHeuristicaAccesibilidad(); 
         break;
      case 3: 
         tablero.setHeuristicaMirada(); 
         break;
   }

   if(fila_inicial> -1 && col_inicial> -1)
   {
      int exitos = 0;
      int media = 0;
      int intentos = 1000;

      Caballo caballo(fila_inicial,col_inicial,tablero);
      caballo.recorridosExitosos(intentos,exitos,media);

      cout << "Casillas visitadas en el ultimo recorrido:" << endl;
      caballo.imprimeCasillasVisitadas();

      cout << "Resultados al intentar completar el recorrido " << intentos << " veces:" << endl;
      cout << " - Exitos (recorridos completos): " << exitos << endl;
      cout << " - Media de movimientos por recorrido: " << media << endl; 
   }
   else
   {
      fila_inicial = 0;
      col_inicial = 0;

      int casillas_a_probar = 64;
      int exitos[64];
      int media[64];
      int intentos = 1000;

      cout << "Tabla con la posicion inicial del caballo ,la media de movimientos" << endl;
      cout << "y el numero de exitos por cada " << intentos << " intentos de recorridos." << endl;
      cout << endl;

      Caballo caballo(fila_inicial,col_inicial,tablero);

      for (int i = 0; i < casillas_a_probar; ++i)
      {
         exitos[i] = 0;
         media[i] = 0;

         caballo.reset(fila_inicial,col_inicial);
         caballo.recorridosExitosos(intentos,exitos[i],media[i]);

         imprimeDato(fila_inicial,col_inicial,exitos[i],media[i],i);

         if (col_inicial < 7)
         {
            col_inicial++;
         }  
         else
         {
            col_inicial = 0;
            fila_inicial++;
         }
      }

      cout << endl;
   }

}

void eligePosInicial(int &fila_inicial, int &col_inicial)
{
   cout << "\nTablero de ajedrez 8x8 numerado por filas y columnas: " << endl;
   cout << "\n       0 , 1 , 2 , 3 , 4 , 5 , 6 , 7"   << endl;
   cout << "   0 |¨¨¨.¨¨¨.¨¨¨.¨¨¨.¨¨¨.¨¨¨.¨¨¨.¨¨¨|" << endl;
   cout << "   1 |   .   .   .   .   .   .   .   |" << endl;
   cout << "   2 |   .   .   .   .   .   .   .   |" << endl;
   cout << "   3 |   .   .   .   .   .   .   .   |" << endl;
   cout << "   4 |   .   .   .   .   .   .   .   |" << endl;
   cout << "   5 |   .   .   .   .   .   .   .   |" << endl;
   cout << "   6 |   .   .   .   .   .   .   .   |" << endl;
   cout << "   7 |   .   .   .   .   .   .   .   |" << endl;
   cout << "     ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨" << endl;

   cout << "¿Posicion inicial del caballo? (-1 -1 para probar todas las casillas). " << endl;
   cout << "Fila/col: ";

   cin >> fila_inicial; 
   cin >> col_inicial;

   while (fila_inicial<-1 || fila_inicial>7 || col_inicial<-1 || col_inicial>7)
   {
         cin >> fila_inicial;
         cin >> col_inicial;
   }
}

void eligeHeuristica(int &opcion)
{
   cout << "\nElija una opcion (introduzca el numero correspondiente):" << endl;
   cout << " 1) Sin heuristica." << endl;
   cout << " 2) Con heuristica de accesibilidad." << endl;
   cout << " 3) Con heuristica de accesibilidad y mirada un paso hacia delante." << endl;

   cout << "Opcion:";
   do{
      cin >> opcion;
   }while (opcion<=0 || opcion>=4);
   cout << endl;
}

void imprimeDato(int &fila,int &col,int &exitos,int &media,int &i)
{
   cout << "(" << fila << "," << col << ")";
   cout << ", " << media << "-" << exitos;

   if (exitos<100)
   {
      cout << " ";

      if(exitos<10)
      {
         cout << " ";
      }
   }

   if (i%4 == 3)
   {
      cout << endl;
   }
   else
   {
      cout << " | ";
   }
}