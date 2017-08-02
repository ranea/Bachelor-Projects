#ifndef MATRIZ_HPP
#define MATRIZ_HPP

#include "tuplas.hpp"

/*
 * Matriz4x4.
 *
 * Usamos la representacion en memoria de OpenGL
 * (almacenar columnas en vez de filas)
 *
 * Asi, la matriz quedaría:
 *
 *    a0,0 a0,1 a0,2 a0,3
 *    a1,0 a1,1 a1,2 a1,3
 *    a2,0 a2,1 a2,2 a2,3
 *    a3,0 a3,1 a3,2 a3,3
 */

class Matriz4x4f
{
private:
   float coe[4][4];

public:
   Matriz4x4f();
   Matriz4x4f(float m[4][4],bool traspuesta);
   Matriz4x4f(const Matriz4x4f& m);

   Matriz4x4f& operator=(const Matriz4x4f& m);
   Tupla4f     operator*(Tupla4f& t);

   Matriz4x4f Componer(Matriz4x4f& m);

   // devuelve la matriz identidad
   static Matriz4x4f Identidad( ) ;

   // devuelven una matriz de traslación por dx,dy,dz (o d[X],d[Y],d[Z])
   static Matriz4x4f Traslacion( const float d[3] ) ;
   static Matriz4x4f Traslacion( const float dx, const float dy ,const float dz ) ;

   // devuelve una matriz de escalado por s_x,s_y,s_z
   static Matriz4x4f Escalado( const float sx, const float sy,const float sz ) ;

   // devuelve una matriz de rotación de eje arbitrario (ex,ey,ez)
   static Matriz4x4f Rotacion( const float ang_gra,
         const float ex, const float ey, const float ez ) ;
   static Matriz4x4f RotacionEjeX( const float ang_gra );
   static Matriz4x4f RotacionEjeY( const float ang_gra );
   static Matriz4x4f RotacionEjeZ( const float ang_gra );
};


#endif
