#ifndef MALLA_HPP
#define MALLA_HPP

#include <GL/glew.h>    // incluir en lugar de GL/gl.h
#include <GL/glut.h>

#include "matriz.hpp"
#include "tuplas.hpp"

#include <vector>

enum ModoVisualizacion{PUNTO,ALAMBRE,SOLIDO,AJEDREZ,ATRIBUTO_CARAS,ATRIBUTO_VERTICES};

class MallaTVT
{
private:
   std::vector<Tupla3f> ver;
   std::vector<Tupla3i> tri;
   std::vector<Tupla3i> tri_impares_pares;

   // Atributos de caras y vertices
   std::vector<Tupla3f> col_ver;
   std::vector<Tupla3f> col_tri;
   std::vector<Tupla3f> nor_tri;
   std::vector<Tupla3f> nor_ver;

   // Colores para el dibujado (por defecto negro y gris)
   Tupla3f color_principal;
   Tupla3f color_alternativo;
   Tupla3f color_normal_tri;
   Tupla3f color_normal_ver;

   // Variables para las distintas visualizaciones
   GLenum modo;
   ModoVisualizacion modo_visualizacion;
   bool pintar_modo_ajedrez;
   bool pintar_normal_caras;
   bool pintar_normal_vertices;

public:
   /*
    * Notas del constructor:
    *    - El segundo parametro tiene un valor por defecto (el vector vacio)
    *      para crear una malla sin tener lista de caras
    *    - La lista de triangulos pares-impares, las normales de caras y vertices
    *      y los colores para las normales si se crean automaticamente en el constructor
    */
   MallaTVT(std::vector<float> vertices_ply, std::vector<int> caras_ply = std::vector<int>() );

   unsigned int num_ver();
   unsigned int num_tri();
   unsigned int num_tri_pares();
   unsigned int num_tri_impares();
   GLenum getModo();
   bool getAjedrez();

   void CambiarVisualizacion(ModoVisualizacion nuevo_modo_visualizacion);
   void CambiarModo(GLenum nuevo_modo);
   void setModoAjedrez(bool pintar_modo_ajedrez);
   void setVisualizarNormalCaras(bool pintar_normal_caras);
   void setVisualizarNormalVertices(bool pintar_normal_vertices);

   void creaTriangulosParesImpares();
   void creaNormales();
   void creaColoresSegunNormales();

   float dimension();   // dimension del menor cubo que encierra el objeto

   void Revoluciona(unsigned int N);
   void Barrido(unsigned int N);

   /*
    * Visualizaciones
    */
   void Visualizar();

   void VisualizarVertices();          // no accede a la tabla de triangulos
   void VisualizarNormalesVertices();
   void VisualizarNormalesCaras();

   void Visualizar_BE();      // (begin/end)
   void Visualizar_BE_AT();   // con atributos de caras
   void Visualizar_BE_AV();   // con atributos de vertices
   void Visualizar_VA();      // vertex-array
   void Visualizar_VA_AV();
};

#endif
