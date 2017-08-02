#include "tuplas.hpp"
#include <cmath>

/*
 * Tupla3f
 */

Tupla3f::Tupla3f(){
   for (int i = 0; i < 3; ++i) {
      componentes[0] = 0;
   }
}

Tupla3f::Tupla3f(float x, float y, float z){
   componentes[0] = x;
   componentes[1] = y;
   componentes[2] = z;
}

Tupla3f::Tupla3f(float array[]){
   for (int i = 0; i < 3; ++i) {
      componentes[i] = array[i];
   }
}

Tupla3f::Tupla3f(const Tupla3f& otra_tupla){
   for (int i = 0; i < 3; ++i) {
      componentes[i] = otra_tupla[i];
   }
}

Tupla3f::Tupla3f(const Tupla4f& tupla4f){
   for (int i = 0; i < 3; ++i) {
      componentes[i] = tupla4f[i];
   }
}

Tupla3f& Tupla3f::operator=(const Tupla3f& otra_tupla){
   if(this != &otra_tupla){
      for (int i = 0; i < 3; ++i) {
         componentes[i] = otra_tupla[i];
      }
   }
   return *this;
}

float& Tupla3f::operator[](unsigned int i){
   return componentes[i];
}

const float& Tupla3f::operator[](unsigned int i) const{
   return componentes[i];
}

bool Tupla3f::operator==(const Tupla3f& otra_tupla)
{
   for (int i = 0; i < 3; ++i)
      if(componentes[i]!=otra_tupla[i])
         return false;

   return true;
}

bool Tupla3f::operator!=(const Tupla3f& otra_tupla)
{
   return !(*this==otra_tupla);
}

Tupla3f Tupla3f::operator+(const Tupla3f& otra_tupla){
   Tupla3f temp = Tupla3f();

   for (int i = 0; i < 3; ++i) {
      temp[i] = componentes[i]+otra_tupla[i];
   }

   return temp;
}

Tupla3f& Tupla3f::operator+=(const Tupla3f& otra_tupla){
   for (int i = 0; i < 3; ++i) {
      componentes[i] += otra_tupla[i];
   }

   return *this;
}

Tupla3f Tupla3f::operator-(const Tupla3f& otra_tupla){
   Tupla3f temp = Tupla3f();

   for (int i = 0; i < 3; ++i) {
      temp[i] = componentes[i]-otra_tupla[i];
   }

   return temp;
}

Tupla3f& Tupla3f::operator-=(const Tupla3f& otra_tupla){
   for (int i = 0; i < 3; ++i) {
      componentes[i] -= otra_tupla[i];
   }

   return *this;
}

Tupla3f Tupla3f::operator*(float componente){
   Tupla3f temp = Tupla3f();

   for (int i = 0; i < 3; ++i) {
      temp[i] = componentes[i]*componente;
   }

   return temp;
}

Tupla3f Tupla3f::operator/(float componente){
   Tupla3f temp = Tupla3f();

   for (int i = 0; i < 3; ++i) {
      temp[i] = componentes[i]/componente;
   }

   return temp;
}

Tupla3f Tupla3f::operator*(const Tupla3f& otra_tupla){
   return Tupla3f(
         componentes[1]*otra_tupla[2] - componentes[2]*otra_tupla[1] ,
         componentes[2]*otra_tupla[0] - componentes[0]*otra_tupla[2] ,
         componentes[0]*otra_tupla[1] - componentes[1]*otra_tupla[0]
      );
}

float Tupla3f::operator|(const Tupla3f& otra_tupla){
   float producto_escalar;

   for (int i = 0; i < 3; ++i) {
      producto_escalar += componentes[i]*otra_tupla[i];
   }

   return producto_escalar;
}

float Tupla3f::lenSq()
{
   return *this|*this;
}

float Tupla3f::len()
{
   return sqrtf( lenSq() );
}

float* Tupla3f::getPuntero() {
   return &(componentes[0]);
}

Tupla3f Tupla3f::normalized()
{
   return *this/len();
}

Tupla3f Tupla3f::abs()
{
   Tupla3f temp = Tupla3f();

   for (int i = 0; i < 3; ++i)
         temp[i] = std::abs(componentes[i]);

   return temp;
}

std::ostream& operator<<(std::ostream& f, const Tupla3f &t)
{
   f << "(" << t[0] << "," << t[1] << "," << t[2] << ")" << std::flush;
   return f;
}


/*
 * Tupla3i
 */

Tupla3i::Tupla3i(){
   for (int i = 0; i < 3; ++i) {
      componentes[0] = 0;
   }
}
Tupla3i::Tupla3i(int x, int y, int z){
   componentes[0] = x;
   componentes[1] = y;
   componentes[2] = z;
}
Tupla3i::Tupla3i(int array[]){
   for (int i = 0; i < 3; ++i) {
      componentes[i] = array[i];
   }
}
Tupla3i::Tupla3i(const Tupla3i& otra_tupla){
   for (int i = 0; i < 3; ++i) {
      componentes[i] = otra_tupla[i];
   }
}

Tupla3i& Tupla3i::operator=(const Tupla3i& otra_tupla){
   if(this != &otra_tupla){
      for (int i = 0; i < 3; ++i) {
         componentes[i] = otra_tupla[i];
      }
   }
   return *this;
}

int& Tupla3i::operator[](unsigned int i){
   return componentes[i];
}

const int& Tupla3i::operator[](unsigned int i) const{
   return componentes[i];
}

bool Tupla3i::operator==(const Tupla3i& otra_tupla)
{
   for (int i = 0; i < 3; ++i)
      if(componentes[i]!=otra_tupla[i])
         return false;

   return true;
}

bool Tupla3i::operator!=(const Tupla3i& otra_tupla)
{
   return !(*this==otra_tupla);
}

/*Tupla3i Tupla3i::operator+(const Tupla3i& otra_tupla){
   Tupla3i temp = Tupla3i();

   for (int i = 0; i < 3; ++i) {
      temp[i] = componentes[i]+otra_tupla[i];
   }

   return temp;
}

Tupla3i Tupla3i::operator-(const Tupla3i& otra_tupla){
   Tupla3i temp = Tupla3i();

   for (int i = 0; i < 3; ++i) {
      temp[i] = componentes[i]-otra_tupla[i];
   }

   return temp;
}*/

int* Tupla3i::getPuntero() {
   return &(componentes[0]);
}

std::ostream& operator<<(std::ostream& f, const Tupla3i &t)
{
   f << "(" << t[0] << "," << t[1] << "," << t[2] << ")" << std::flush;
   return f;
}

/*
 * Tupla4f
 */

Tupla4f::Tupla4f(){
   for (int i = 0; i < 4; ++i) {
      componentes[0] = 0;
   }
}

Tupla4f::Tupla4f(float x, float y, float z, float t){
   componentes[0] = x;
   componentes[1] = y;
   componentes[2] = z;
   componentes[3] = t;
}

Tupla4f::Tupla4f(float array[]){
   for (int i = 0; i < 4; ++i) {
      componentes[i] = array[i];
   }
}

Tupla4f::Tupla4f(const Tupla4f& otra_tupla){
   for (int i = 0; i < 4; ++i) {
      componentes[i] = otra_tupla[i];
   }
}

Tupla4f::Tupla4f(const Tupla3f& tupla3f){
   for (int i = 0; i < 3; ++i) {
      componentes[i] = tupla3f[i];
   }
   componentes[3] = 1;
}

Tupla4f& Tupla4f::operator=(const Tupla4f& otra_tupla){
   if(this != &otra_tupla){
      for (int i = 0; i < 4; ++i) {
         componentes[i] = otra_tupla[i];
      }
   }
   return *this;
}

float& Tupla4f::operator[](unsigned int i){
   return componentes[i];
}

const float& Tupla4f::operator[](unsigned int i) const{
   return componentes[i];
}

bool Tupla4f::operator==(const Tupla4f& otra_tupla)
{
   for (int i = 0; i < 4; ++i)
      if(componentes[i]!=otra_tupla[i])
         return false;

   return true;
}

bool Tupla4f::operator!=(const Tupla4f& otra_tupla)
{
   return !(*this==otra_tupla);
}

Tupla4f Tupla4f::operator+(const Tupla4f& otra_tupla){
   Tupla4f temp = Tupla4f();

   for (int i = 0; i < 4; ++i) {
      temp[i] = componentes[i]+otra_tupla[i];
   }

   return temp;
}

Tupla4f& Tupla4f::operator+=(const Tupla4f& otra_tupla){
   for (int i = 0; i < 4; ++i) {
      componentes[i] += otra_tupla[i];
   }

   return *this;
}

Tupla4f Tupla4f::operator-(const Tupla4f& otra_tupla){
   Tupla4f temp = Tupla3f();

   for (int i = 0; i < 4; ++i) {
      temp[i] = componentes[i]-otra_tupla[i];
   }

   return temp;
}

Tupla4f& Tupla4f::operator-=(const Tupla4f& otra_tupla){
   for (int i = 0; i < 4; ++i) {
      componentes[i] -= otra_tupla[i];
   }

   return *this;
}

Tupla4f Tupla4f::operator*(float componente){
   Tupla4f temp = Tupla4f();

   for (int i = 0; i < 4; ++i) {
      temp[i] = componentes[i]*componente;
   }

   return temp;
}

Tupla4f Tupla4f::operator/(float componente){
   Tupla4f temp = Tupla4f();

   for (int i = 0; i < 4; ++i) {
      temp[i] = componentes[i]/componente;
   }

   return temp;
}

float Tupla4f::operator|(const Tupla4f& otra_tupla){
   float producto_escalar;

   for (int i = 0; i < 4; ++i) {
      producto_escalar += componentes[i]*otra_tupla[i];
   }

   return producto_escalar;
}

float Tupla4f::lenSq()
{
   return *this|*this;
}

float Tupla4f::len()
{
   return sqrtf( lenSq() );
}

float* Tupla4f::getPuntero() {
   return &(componentes[0]);
}

Tupla4f Tupla4f::normalized()
{
   return *this/len();
}

Tupla4f Tupla4f::abs()
{
   Tupla4f temp = Tupla4f();

   for (int i = 0; i < 4; ++i)
         temp[i] = std::abs(componentes[i]);

   return temp;
}

std::ostream& operator<<(std::ostream& f, const Tupla4f &t)
{
   f << "(" << t[0] << "," << t[1] << "," << t[2] << ")" << std::flush;
   return f;
}

 
