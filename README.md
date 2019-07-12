# GameOfLife
A c++ build of Conway's Game of Life using 2D arrays.

To run, use command: ./a
OR
To compile and run from scratch:
in directory where files are saved, run commands:
g++ .h files
g++ -c .cpp files
g++ -o name_of_executable Start.o PGArray.o main.o

# Features
Choice to start with either:
-Initial game board chosen in game

-Initial game board loaded on a text file chosen in game

format of file: 

line 1 - number of rows

line 2 - number of columns

next lines - layout of initial game board using 'X' as a cell and any other character as empty space.

Example:
```
4
4
X-X-
-XX-
---X
XXXX
```

## Choice to play game by:
1. having a 1 second pause after each generation
2. pressing "ENTER" to proceed to next generation
3. outputting results of game to a text file of choice

## 3 game modes:

### Classic Mode - uses 4 regular rules
from Wikipedia:
1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
2. Any live cell with two or three live neighbours lives on to the next generation.
3. Any live cell with more than three live neighbours dies, as if by overpopulation.
4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

### Mirror Mode:
Adds rule:
5. Any cell on an edge is mirrored so that its reflection(s) also count as cells.
Example:
if board is normally this:
```
  X - -
  - X X
  - x -
```
  
then in mirror mode it would act like this: (mirrored cells in lower case x)
```
  x
x X - - 
  - X X x
  - X -
    x
```

### Donut Mode:
Adds rule:
5. Any cell on an edge is wrapped around to the opposite side so that its wrapped counterpart(s) also count as cells.
Example:
if board is normally this:
```
  X - -
  - X X
  - x -
```
  
then in donut mode it would act like this: (wrapped cells in lower case x)
```
    x
  X - - x
x - X X 
  - X -
  x 
```
