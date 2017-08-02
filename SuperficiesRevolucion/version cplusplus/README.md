# Superficies de revolución

## Modo de uso:

	./revol curvas.txt Paso ExtrInf ExtreSup Revoluciones

donde:
      
 - curvas.txt: fichero de texto donde esta la curva definida en ecuaciones paramétricas. La primera linea contiene la primera ecuación paramétrica de la curva y la segunda línea la segunda ecuación paramétrica. 
 - paso: entero (o decimal) que representa el espaciado al muestrear los puntos. Por ejemplo, si se toma paso=1, se tomara cada valor de la curva de una en una unidad.
 - ExtrInf: entero (o decimal) que representa el limite inferior del intervalo a muestrear
 - ExtrSup: entero (o decimal) que representa el limite superior del intervalo a muestrear
 - Revoluciones: el número de copias que se hacen de la curva orignal en el eje Z. Por ejemplo si se toma 360, se copia la curva para cada grado. Se recomienda 45.


## Ejemplos:

- esfera unidad

		cos(t)
		sin(t)

- cilindro vertical de radio 1

		1
		t

- hiperboloide reglado

		cosh(t)
		sinh(t)

- una hoja del hiperboloide eliptico, t>0

		sinh(t)
		cosh(t)

- otra hoja del hiperboloide eliptico

		sinh(t)
		-cosh(t)

- una componente del cono, t>0

		t
		t

- otra componente del cono

		t
		-t

- toro de revolucion 

		2*(3 + cos(t))
		2*sin(t)

- catenoide

		cosh(t)
		t
                               
##Ecuaciones

Para el fichero curvas.txt se pueden usar los siguientes elementos:

 - operadores básicos: 
	
		+, -, *, /, %, ^
        
 - funciones: 

		abs, exp, log, log10, log2, logn, max,  min,  root, sqrt
        
 - funciones trigonometricas: 

		acos, acosh, asin, asinh, atan, atanh,  atan2, cos,  cosh, cot,  csc, sec,  sin, sinc,  sinh, tan, tanh
                       

## Descripción de las teclas:

Durante la ejecucción del programa, están las siguientes acciones disponibles:

	1: modo punto
	2: modo alambre
	3: modo sólido
	4: modo ajedrez
	5: colores cara según normales cara
	6: colores vertices según normales vértices
	c: pintar las normales de cara
	C: no pintar las normales de cara
	v: pintar las normales de vértices 
	V: no pintar las normales de vértices

