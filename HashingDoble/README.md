# HashingDoble
Disponemos de una funcion hash

*h(k) = k% M (M primo)*

y de un metodo de resolucion de colisiones siguiendo un esquema de hashing doble a traves de la funcion:

*h_i(k) = [ h(k) + d_i ]% M i=2,3,4,....*

con d_i calculado como:

*d_i=[a * d_i-􀀀1 + c]% M con d_0=0*

Se trata de encontrar para un valor de M (p.ej. M=16) una combinacion de valores de a y de c que den lugar a una secuencia de d_i que no cicle antes de tiempo, es decir una secuencia de valores que garantice el acceso a todos los posibles huecos de la tabla cara a la insercion de nuevas claves.

Hay dos partes:
 - Un sencillo procedimiento de simulacion,  que encuentra las parejas (a,c) que dan lugar a un esquema de hashing valido (sucesion que no cicle antes de tiempo).
 - Soluciones teoricas independientemente del tamaño M de la tabla que tengamos.
