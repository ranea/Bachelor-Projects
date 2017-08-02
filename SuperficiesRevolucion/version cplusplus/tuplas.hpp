#ifndef TUPLAS_HPP
#define TUPLAS_HPP

#include <iostream>

class Tupla3f;
class Tupla3i;
class Tupla4f;

class Tupla3f
{
private:
   float componentes[3];

public:
   Tupla3f();
   Tupla3f(float x, float y, float z);
   Tupla3f(float array[]);
   Tupla3f(const Tupla3f& otra_tupla);
   Tupla3f(const Tupla4f& tupla4f);       // ignoramos la cuarta componente

   float&         operator[]  (unsigned int i);
   const float&   operator[]  (unsigned int i) const;
   Tupla3f&       operator=   (const Tupla3f& otra_tupla);
   bool           operator==  (const Tupla3f& otra_tupla);
   bool           operator!=  (const Tupla3f& otra_tupla);

   Tupla3f  operator+ (const Tupla3f& otra_tupla);
   Tupla3f& operator+=(const Tupla3f& otra_tupla);
   Tupla3f  operator- (const Tupla3f& otra_tupla);
   Tupla3f& operator-=(const Tupla3f& otra_tupla);
   Tupla3f  operator* (float componente);            // Producto por escalar
   Tupla3f  operator/ (float componente);            // Division por escalar
   Tupla3f  operator* (const Tupla3f& otra_tupla);   // Producto vectorial (solo para R3)
   float    operator| (const Tupla3f& otra_tupla);   // Producto escalar

   float lenSq();
   float len();

   float* getPuntero();

   Tupla3f normalized();
   Tupla3f abs();

   friend std::ostream& operator<<(std::ostream &f, const Tupla3f &t);
};

class Tupla3i
{
private:
   int componentes[3];

public:
   Tupla3i();
   Tupla3i(int x, int y, int z=0);
   Tupla3i(int array[]);
   Tupla3i(const Tupla3i& otra_tupla);

   Tupla3i&       operator=   (const Tupla3i& otra_tupla);
   int&           operator[]  (unsigned int i);
   const int&     operator[]  (unsigned int i) const;
   bool           operator==  (const Tupla3i& otra_tupla);
   bool           operator!=  (const Tupla3i& otra_tupla);

   //Tupla3i operator+ (const Tupla3i& otra_tupla);
   //Tupla3i operator- (const Tupla3i& otra_tupla);

   int* getPuntero();

   friend std::ostream& operator<<(std::ostream &f, const Tupla3i &t);
};

class Tupla4f
{
private:
   float componentes[4];

public:
   Tupla4f();
   Tupla4f(float x, float y, float z, float t);
   Tupla4f(float array[]);
   Tupla4f(const Tupla4f& otra_tupla);
   Tupla4f(const Tupla3f& tupla3f);       // la 4º componente la hacemos 1

   float&         operator[]  (unsigned int i);
   const float&   operator[]  (unsigned int i) const;
   Tupla4f&       operator=   (const Tupla4f& otra_tupla);
   bool           operator==  (const Tupla4f& otra_tupla);
   bool           operator!=  (const Tupla4f& otra_tupla);

   Tupla4f  operator+ (const Tupla4f& otra_tupla);
   Tupla4f& operator+=(const Tupla4f& otra_tupla);
   Tupla4f  operator- (const Tupla4f& otra_tupla);
   Tupla4f& operator-=(const Tupla4f& otra_tupla);
   Tupla4f  operator* (float componente);            // Producto por escalar
   Tupla4f  operator/ (float componente);            // Division por escalar
   float    operator| (const Tupla4f& otra_tupla);   // Producto escalar

   float lenSq();
   float len();

   float* getPuntero();

   Tupla4f normalized();
   Tupla4f abs();

   friend std::ostream& operator<<(std::ostream &f, const Tupla4f &t);
};

#endif
