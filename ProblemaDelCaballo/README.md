# Problema del caballo
El problema del caballo es dado una cuadrícula de n x n casillas y un caballo de ajedrez colocado en una posición cualquiera ( x, y ), ver si el caballo puede por todas las casillas y una sola vez.

En este caso se hace para un tablero 8x8.

Para ello se elaboran tres estrategias:
 - Sin heurística (el movimiento es aleatorio)
 - Heurística de accesibilidad
 - Heurística de accesibilidad y mirada un paso hacia delante

# Heurística de accesibilidad
Clasificamos cada casilla de acuerdo a cómo de accesible es (desde cuantas posiciones se pueden llegar a ella) y después seleccionamos para el siguiente movimiento la más inacessible.

# Heurística de mirada un paso hacia delante
Se resuelven los empates entre posibles movimientos a casillas con igual accesibilidad mirando los posibles movimientos a partir de las casillas empatadas y valorando su accesibilidad.
