#include "matriz.hpp"
#include <cmath>

Matriz4x4f::Matriz4x4f()
{
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         coe[j][i] = 0;
}

Matriz4x4f::Matriz4x4f(float m[4][4], bool traspuesta)
{
   if(traspuesta){
      for (int i = 0; i < 4; i++)
         for (int j = 0; j < 4; j++)
            coe[j][i] = m[j][i];
   }
   else{
      for (int i = 0; i < 4; i++)
         for (int j = 0; j < 4; j++)
            coe[j][i] = m[i][j];
   }
}

Matriz4x4f::Matriz4x4f(const Matriz4x4f& m)
{
   for (int i = 0; i < 4; i++)
      for (int j = 0; j < 4; j++)
         coe[j][i] = m.coe[j][i];
}

Matriz4x4f& Matriz4x4f::operator=(const Matriz4x4f& m)
{
   if (this != &m)
   {
      for (int i = 0; i < 4; i++)
         for (int j = 0; j < 4; j++)
            coe[j][i] = m.coe[j][i];
   }
   return *this;
}

Matriz4x4f Matriz4x4f::Componer(Matriz4x4f& m)
{
   Matriz4x4f res;

   for( unsigned fil = 0 ; fil < 4 ; fil++ ){
      for( unsigned col = 0 ; col < 4 ; col++ ){

         for( unsigned k = 0 ; k < 4 ; k++ )
            res.coe[col][fil] += coe[k][fil]*m.coe[col][k] ;
      }
   }

   return res ;
}

Tupla4f Matriz4x4f::operator*(Tupla4f& t)
{
   Tupla4f res = Tupla4f(0,0,0,0);

   for( unsigned fila = 0 ; fila < 4 ; fila++ )   {
      for( unsigned colu = 0 ; colu < 4 ; colu++ ){
         res[fila] += coe[colu][fila]*t[colu] ;
      }
   }

   return res;
}

Matriz4x4f Matriz4x4f::Identidad()
{
   float matriz[4][4] = {
         {1,0,0,0},
         {0,1,0,0},
         {0,0,1,0},
         {0,0,0,1}
   };

   return Matriz4x4f(matriz,false);
}

Matriz4x4f Matriz4x4f::Traslacion( const float d[3] )
{
   float matriz[4][4] = {
         {1,0,0,d[0]},
         {0,1,0,d[1]},
         {0,0,1,d[2]},
         {0,0,0,1}
   };

   return Matriz4x4f(matriz,false);
}
Matriz4x4f Matriz4x4f::Traslacion( const float dx, const float dy ,const float dz )
{
   float matriz[4][4] = {
         {1,0,0,dx},
         {0,1,0,dy},
         {0,0,1,dz},
         {0,0,0,1}
   };

   return Matriz4x4f(matriz,false);
}

Matriz4x4f Matriz4x4f::Escalado( const float sx, const float sy,const float sz )
{
   float matriz[4][4] = {
         {sx,0,0,0},
         {0,sy,0,0},
         {0,0,sz,0},
         {0,0,0,1}
   };

   return Matriz4x4f(matriz,false);
}

Matriz4x4f Matriz4x4f::Rotacion( const float ang_gra,
      const float ex, const float ey, const float ez )
{
   float c = cosf(ang_gra);
   float s = sinf(ang_gra);
   float hx = (1-c)*ex;
   float hy = (1-c)*ey;
   float hz = (1-c)*ez;


   float matriz[4][4] = {
         {hx*ex+c,      hx*ey-s*ez, hx*ez+s*ey, 0},
         {hy*ex+s*ez,   hy*ey+c,    hy*ez-s*ex, 0},
         {hz*ex-s*ey,   hz*ey+s*ez, hz*ez+c,    0},
         {0,            0,          0,          1}
   };

   return Matriz4x4f(matriz,false);
}

Matriz4x4f Matriz4x4f::RotacionEjeX( const float ang_gra ){
   float c = cosf(ang_gra);
   float s = sinf(ang_gra);

   float matriz[4][4] = {
         {1,0,0,0},
         {0,c,-s,0},
         {0,s,c,0},
         {0,0,0,1}
   };

   return Matriz4x4f(matriz,false);
}
Matriz4x4f Matriz4x4f::RotacionEjeY( const float ang_gra ){
   float c = cosf(ang_gra);
   float s = sinf(ang_gra);

   float matriz[4][4] = {
         {c,0,s,0},
         {0,1,0,0},
         {-s,0,c,0},
         {0,0,0,1}
   };

   return Matriz4x4f(matriz,false);
}
Matriz4x4f Matriz4x4f::RotacionEjeZ( const float ang_gra ){
   float c = cosf(ang_gra);
   float s = sinf(ang_gra);

   float matriz[4][4] = {
         {c,-s,0,0},
         {s,c,0,0},
         {0,0,1,0},
         {0,0,0,1}
   };

   return Matriz4x4f(matriz,false);
}
