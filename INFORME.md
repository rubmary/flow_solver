Departamento de Computación<br>
Inteligencia Artificial I – CI5437<br>
Prof. Blai Bonet<br>
Rubmary Rojas 13-11264  <br>
Fernando Yánez 13-11506 <br>
<br>

# Informe Proyecto 4
## Flow game

# 1. Resumen

El objetivo del proyecto fue construir un solucionador de juegos "Flow" utilizando un *SAT solver*, para lo cual primero se creó una teoría proposicional &Delta; tal que la teoría es satisfacible si y sólo si el juego tiene solución y cada solución del juego está en correspondencia con un modelo de la teoría.

Para esto se realizó lo siguiente:
1. Un codificador que, dado una configuracion inicial de Flow, lo traduce en una teoría proposicional &Delta;
2. Un decodificador que, dado un modelo de la teoría, lo decodifica a una solución del juego y crea una imagen correspondiente a la solución.
3. Un script que utiliza el codificador, decodificador y el SAT solver *minisat* para resolver los juegos del benchmark utilizado.

# 2. Teoría proposicional &Delta;

## Variables

Se utilizaron las siguientes variables para la teoría &Delta;

| variable | interpretación |
| :-- | :-- |
| c(i, j, r) | La celda (i, j) se encuentra encendida de color r |
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
