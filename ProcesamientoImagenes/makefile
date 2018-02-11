##################################################################################
#
#	Makefile para la gestión de las dependencias 
#	de los programas que usan los T.D.A Imagen y Vídeo.
#
#	Uso: make -> Compila todos los programas y genera documentación con Doxygen
#       make clean -> Borra de la carpeta los ejecutables y la documentación
#
#	Autores: Antonio Álvarez Caballero y Adrián
#
#
##################################################################################


INCLUDE=./

all: presentar morphing rebobinar umbralizar contraste zoom icono documentacion

presentar:
	@echo
	@echo Dentro de cada cpp existen instrucciones detalladas para cada programa,
	@echo pero se presenta brevemente la sintaxis de cada uno de ellos.
	@echo 
morphing: imagenES.cpp video.h morphing.cpp utilidades.cpp
	@echo
	@echo Compilando $@...
	@g++ -g -o $@ $^ -I$(INCLUDE)
	@echo Uso: ./$@ \<fichOri\> \<fichDest\> \<k\> \<pref\>
	@echo
rebobinar: imagenES.cpp video.h rebobinar.cpp utilidades.cpp
	@echo Compilando $@...
	@g++ -g -o $@ $^ -I$(INCLUDE)
	@echo Uso: ./$@ \<prefOri\> \<nframes\> \<prefDest\>
	@echo
umbralizar: imagenES.cpp imagen.h umbralizar.cpp utilidades.cpp
	@echo Compilando $@...
	@g++ -g -o $@ $^ -I$(INCLUDE)
	@echo Uso: ./$@ \<fichOri\> \<fichDest\> \<T1\> \<T2\>
	@echo
contraste: imagenES.cpp imagen.h contraste.cpp utilidades.cpp
	@echo Compilando $@...
	@g++ -g -o $@ $^ -I$(INCLUDE)
	@echo Uso: ./$@ \<fichOri\> \<fichDest\> \<min\> \<max\>
	@echo
zoom: imagenES.cpp imagen.h zoom.cpp utilidades.cpp
	@echo Compilando $@...
	@g++ -g -o $@ $^ -I$(INCLUDE)
	@echo Uso: ./$@ \<fichE\> \<fichS\> \<x1\> \<y2\> \<x2\> \<y2\>
	@echo
icono: imagenES.cpp imagen.h icono.cpp utilidades.cpp
	@echo Compilando $@...
	@g++ -g -o $@ $^ -I$(INCLUDE)
	@echo Uso: ./$@ \<fichE\> \<fichS\> \<nf\> \<nc\>
	@echo
documentacion: imagen.h video.h
	@echo Generando documentación...
	@doxygen Doxyfile &> /dev/null
	@cd latex && make &> /dev/null && cp refman.pdf ../doxygen.pdf && cd .. && rm -r latex
	@echo La documentación se encuentra en el archivo doxygen.pdf y en la carpeta html
	@echo 
clean:
	@echo Limpiando ejecutables y documentación...
	@rm -v morphing rebobinar umbralizar contraste zoom icono doxygen.pdf
	@rm -r html/*
	@rm -v -r html