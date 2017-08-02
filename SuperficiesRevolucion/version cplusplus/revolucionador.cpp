#include "revolucionador.hpp"
#include "file_ply_stl.h"
#include <assert.h>
#include <string>
#include "exprtk.hpp"
#include <stdio.h>
#include <stdlib.h> 

MallaTVT * R_pm;
std::vector<float> vertices_ply ;

void R_DibujarFigura()
{
   R_pm->Visualizar();
}

void R_EvaluarFuncion(
   std::string ecuacion1, std::string ecuacion2,
   double paso, double extremo_inf, double extremo_sup )
{
   double t;   // variable

   exprtk::symbol_table<double> symbol_table;
   symbol_table.add_variable("t",t);
   symbol_table.add_constants();

   exprtk::expression<double> expression1;
   expression1.register_symbol_table(symbol_table);
   exprtk::expression<double> expression2;
   expression2.register_symbol_table(symbol_table);

   exprtk::parser<double> parser;
   parser.compile(ecuacion1,expression1);
   parser.compile(ecuacion2,expression2);

   for (t = extremo_inf; t <= extremo_sup; t += paso)
   {
      vertices_ply.push_back(expression1.value());
      vertices_ply.push_back(expression2.value());
      vertices_ply.push_back(0);
   }
}

/*
 * Se llama una vez al inicio, cuando ya se ha creado la ventana e
 * incializado OpenGL. 
 */
void R_Inicializar( int argc, char *argv[] )
{
   /*
    * 1º arg = fichero con x(t),y(t)
    * 2º arg = espaciado al muestrear los puntos (paso)
    * 3º arg = extremo inferior del intervalo
    * 4º arg = extremo superior del intervalo
    * 5º arg = nº de copias del perfil, incluyendo la original
    */
   assert(argc >= 5);

   // leemos las ecuaciones parametricas del fichero
   FILE * fichero;
   char buffer [100];
   std::string ecuacion_parametrica1;
   std::string ecuacion_parametrica2;

   fichero = fopen (argv[1] , "r");

   if (fichero == NULL) 
      perror ("Error opening file");
   else{
      if ( fgets (buffer , 100 , fichero) == NULL ) 
         perror ("Fichero vacio");
      else
         ecuacion_parametrica1 = buffer;

      if ( fgets (buffer , 100 , fichero) == NULL ) 
         perror ("Falta la segunda ecuacion paramétrica");
      else
         ecuacion_parametrica2 = buffer;     
   }

   //debug
   std::cout << "| Curva |" << std::endl;
   std::cout << ecuacion_parametrica1 << ecuacion_parametrica2;

   double paso = atof(argv[2]);
   double inf = atof(argv[3]);
   double sup = atof(argv[4]);

   R_EvaluarFuncion(ecuacion_parametrica1,ecuacion_parametrica2,paso,inf,sup);

   unsigned int N = atoi(argv[5]);

   R_pm = new MallaTVT(vertices_ply);

   R_pm->Revoluciona(N);   
}

void R_DibujarObjetos()
{
   R_DibujarFigura();
}
