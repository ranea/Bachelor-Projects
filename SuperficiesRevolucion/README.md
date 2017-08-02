# Superficies de revolución

Programa que pinta superficies de revolución rotando una curva plana dada.

## Modo de uso:

La versión en python cuenta con una interfaz gráfica intuitiva y está más completa. Basta ejecutar GUI.py y proporcionar los datos que se piden.

También se dispone una versión en C++ sin interfaz que para ejecutarla deberá leer el readme correspondiente.

## Ejemplos:

Se muestran algunos ejemplos de curvas planas que se pueden utilizar.

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
                               




