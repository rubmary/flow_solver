Departamento de Computación<br>
Inteligencia Artificial I – CI5437<br>
Prof. Blai Bonet<br>
Rubmary Rojas 13-11264  <br>
Fernando Yánez 13-11506 <br>
<br>

# Informe Proyecto 4
## Flow game

# 1. Resumen

El objetivo del proyecto fue construir un solucionador de juegos "Flow". El juego consta de un tablero NxM, el cual inicialmente tiene 2R círculos, de R colores diferentes con exactamente 2 círculos por color, en celdas diferentes del tablero y el resto del tablero se encuentra vacío. El objetivo del juego consiste en conectar cada par de puntos del mismo color formando un camino con celdas que compartan un lado, sin que los caminos se intersecten y si dejar celdas vacías.

Así pues, se utilizó un *SAT solver*, para lo cual primero se creó una teoría proposicional &Delta; tal que la teoría tiene una solución $acíclica$ si y sólo si el juego tiene solución y cada solución del juego está en correspondencia con un modelo de la teoría. Solución $acíclica$ significa que no se tienen ciclos en el grafo generado al considerar las celdas como vértices y los arcos los lados que pertenezcan a dos celdas del mismo color.

Para esto se realizó lo siguiente:
1. Un codificador que, dado una configuracion inicial de Flow, lo traduce en una teoría proposicional &Delta;
2. Un decodificador que, dado un modelo de la teoría, lo decodifica a una solución del juego y crea una imagen correspondiente a la solución.
3. Un solucionador que verifica si una solución del juego tiene ciclos, y en caso afirmativo agrega cláusulas correspondientes a cada ciclo y los agrega a la teoría para volver a llamar al minisat. Este proceso se repita hasta que se consiga una solución acíclica
4. Un script que utiliza el codificador, decodificador, el SAT solver *minisat* y el solucionador para resolver los juegos del benchmark utilizado.

# 2. Teoría proposicional &Delta;

## Variables

Se utilizaron las siguientes variables para la teoría &Delta;

| variable | interpretación |
| :-- | :-- |
| c(i, j, r) | La celda (i, j) es de color r |
| d(i, j, k) | La celda (i, j) tiene dirección k |

donde el dominio Dc={ r : r entero y pertenece al intervalo [0,R-1]}, con R igual al número de colores distintos presentes en la configuración inicial,
y Dd = { k : 0 <= k < 10 }. La k-ésima dirección de la celda se muestra en la siguiente tabla:

| k | dirección |
| :-- | :-- |
| 0 | └ |
| 1 | │ |
| 2 | ┘ |
| 3 | ┌ |
| 4 | ─ |
| 5 | ┐ |
| 6 | tu |
| 7 | tr |
| 8 | td |
| 9 | tl |

donde ti es una celda terminal con dirección i; i = u(up), r(right), d(down), l(left).

## Cláusulas

Las cláusulas utilizadas fueron las siguientes:

* Cada casilla tiene un color

$$ (\exist r | 0 \leq r \and r < R | c(i, j, r)) $$

## Cantidad total de cláusulas

La cantidad total de cláusulas es:

| Complejidad|
| :-: |
| (CAMBIAR) O(NM(N + M)K<sup>2</sup><sub>max</sub>) |

## CNF

Todas las cláusulas pueden ser llevadas a un formato CNF, utilizando la propiedad: p &rightarrow; q &Leftrightarrow; &not; p &or; q. Las traducción es directa y no se presentan los detalles.

# 3. Resultados

Las imágenes obtenidas se encuentran en la carpeta *images*. Se lograron resolver 28 de 28 configuraciones iniciales del juego con dificultad variante (número de colores y tamaño del tablero).

Es importante destacar que dado que ninguna celda del tablero puede quedar vacía, dadas las clausulas con las que se trabajó, era posible que se crearan ciclos de cualquier color (no correspondiendo a ninguna celda terminal). Como esto no representa una solución valida para el juego, un primero intento de atacar esto fue unir el conjunto de las negaciones de cada solución con ciclos que fuese propuesta por el SAT-solver con la teoría $Delta inicial del juego. El resultado de esta medida no fue óptimo ya que existían configuraciones en las que no solo se creaban varios ciclos dentro del tablero, sino que la negación de una solución particular no toma en cuenta las combinaciones de los ciclos de todos los colores.

Es por esto que la medida final ante este problema fue reconocer las posiciones del tablero donde se creaban ciclos y negar únicamente el conjunto de variables que representan las direcciones de las celdas que forman parte de él.
