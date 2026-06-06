## Life — short cheat sheet

`Life` = Conway's Game of Life.

Main steps to implement: 7 blocks:
```cpp
//1. struct + index
//2. inside + draw
//3. read input
//4. count neighbors  = C DD NN (C  = count, DD = dx dy, NN = nx ny)
//5. step rules = XY NP (XY = X Y, N  = neighbors, P  = pos)
//6. clear + swap + simulate
//7. print + main cleanup
```
The subject does not explicitly list the rules, but `game of life` usually means the classic Conway rules:

```txt
B3/S23
```

Meaning:

```txt
B3  -> Birth: a dead cell becomes alive if it has exactly 3 alive neighbors.
S23 -> Survival: an alive cell stays alive if it has 2 or 3 alive neighbors.
```

Everything else becomes/stays dead.

```txt
alive + 0 neighbors  -> dead
alive + 1 neighbor   -> dead
alive + 2 neighbors  -> alive
alive + 3 neighbors  -> alive
alive + 4+ neighbors -> dead

dead + 3 neighbors       -> alive
dead + anything else     -> dead
```

Classic example: `blinker`

```txt
Iteration 0:

 O
 O
 O

Iteration 1:

   
OOO
   

Iteration 2:

 O
 O
 O
```

So:

```txt
vertical -> horizontal -> vertical -> ...
```

In code:

```c
if (cell && (neighbors == 2 || neighbors == 3))
	next = 1;
else if (!cell && neighbors == 3)
	next = 1;
else
	next = 0;
```
