#include <iostream>
#include <math.h>
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

bool esPrimo(int entero)
{
   double tope = sqrt(entero);

   for (int i=2; i<=tope; ++i)
   {
      if(entero%i==0)
         return false;
   }
   
   return true;
}

int main(int argc, char const *argv[])
{
   int v[100][50] = {0};
   
   for (M=0; M<100; M++)
   {
      if(!esPrimo(M))
      {
         int i = 0;
         for (int a=2; a<M; ++a)
         {
            if(esCiclica(a,1))
            {
               v[M][i] = a;
               i++;
            }
         }
      }

   }

   for (M=0; M<100; ++M)
   {
      if(v[M][0]!=0)
      {
         cout << "M: " << M << " | ";

         int i=0;
         while(v[M][i]!=0)
         {
            cout << v[M][i] << ", ";
            i++;
         }
         cout << endl;
      }
   }

   return 0;
}