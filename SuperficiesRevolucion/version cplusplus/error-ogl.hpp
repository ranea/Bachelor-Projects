#ifndef ERROR_OGL_HPP
#define ERROR_OGL_HPP

// *********************************************************************
// comprobación de errores de OpenGL

#define CError() CompruebaErrorOpenGL(__FILE__,__LINE__)
void CompruebaErrorOpenGL( const char * nomArchivo, int linea ) ;

// *********************************************************************
// gestion de un error (revisar y quitar version en minusculas)

#define error(msg,donde)   GestionarError(msg,donde,__FILE__,__LINE__)
#define Error(msg,donde)   GestionarError(msg,donde,__FILE__,__LINE__)

void GestionarError( const char * msg, const char * donde, const char * nomArchivo, int linea ) ;

#endif // ERROR_OGL_HPP
