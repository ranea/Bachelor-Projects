#include <iostream>
#include <stdio.h>
#include <stdlib.h>


using namespace std;

static int M;

/* Comprueba si elemento se cuentra en el vector v[] */
bool pertenece(int v[], int util_v, int elemento)
{
   bool pertenece = false;
   
   for (int i=0; i<util_v && !pertenece; ++i)
   {
      pertenece = (v[i] == elemento);
   }

   return pertenece;
}

/* Comprueba si la secuencia de los d_i construida
   a partir del par (a,c) cicla antes de tiempo */
bool esCiclica(int a, int c)
{
   int *v = new int[M];  /**< Vector con los d_i anteriores */
   v[0] = 0;
   int util_v = 1;

   bool no_cicla = true;

   /* Probamos si cicla para M-1 colisiones */ 
   int d_i = 0;
   for (util_v; util_v<M && no_cicla; ++util_v)
   {
      d_i = (a * d_i + c) % M;

      no_cicla = !pertenece(v,util_v,d_i);

      v[util_v] = d_i;
   }

   return no_cicla;
}

int main(int argc, char const *argv[])
{
   M = atoi(argv[1]);

   cout << " ------------ " << M << " ------------ " << endl;


   for (int c=0; c<M; ++c)
   {
      for (int a=0; a<M; ++a)
      {
         if(esCiclica(a,c))
         {
            cout << "| c:" << c << ", a:" << a << " | " << endl;
         }
      }
   }

   cout << " ----------- FIN ------------ " << endl;

   return 0;
}