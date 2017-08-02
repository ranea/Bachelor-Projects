#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>

#include "error-ogl.hpp"

// *********************************************************************
// gestion de errores
   
void GestionarError( const char * msg, const char * donde, const char * nomArchivo, int linea )
{
   std::cout
         << std::endl
         << "-----------------------------------------------------------" << std::endl
         << "Error detectado:" << std::endl
         << "   descripción : " << msg  << "." << std::endl
         << "   archivo     : " << nomArchivo << std::endl  
         << "   lugar       : " << donde << std::endl 
         << "   línea       : " << linea << std::endl
         << "-----------------------------------------------------------" << std::endl
         << "programa abortado." << std:: endl
         << std::flush ;
         
    exit(1) ;
}

void CompruebaErrorOpenGL( const char * nomArchivo, int linea )
{
   const GLint codigoError = glGetError() ;
   
   if ( codigoError != GL_NO_ERROR )
   {  std::cout 
         << std::endl
         << "Detectado error de OpenGL. Programa abortado." << std::endl 
         << "   línea       : "  << linea << std::endl
         << "   archivo     : " << nomArchivo << std::endl 
         << "   descripción : " << gluErrorString(codigoError)  << "." << std::endl
         << std::endl << std::flush ;
      exit(1);
   }
}




   

   
   




