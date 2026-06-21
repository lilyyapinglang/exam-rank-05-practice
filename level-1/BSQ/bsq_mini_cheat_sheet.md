# BSQ — Mini Cheat Sheet

```
READ:
parseHead + saveLine + readMap

SOLVE:
min3 + solveMap + fillSquare

OUTPUT:
printMap

CLEAN:
freeMap

FLOW:
processMap + main
```

```cpp
//1. struct + init - store all map information and reset it before use

//2. parseHead - read the first line of the format: rows empty obstacle full, for example "9 . o x"

//3. saveLine - check one map line, set/compare the width, and save it to the grid

//4. readMap - read the entire map: header, grid lines, check the number of lines and extra input

//5. solveMap - find the largest square using the DP formula min(top, left, diagonal) + 1

//6. fill + print + free - fill the found square, print the map, and free memory

//7. processMap + main - tie everything together: open input, process the map, display the result, or return a map error
```

```text
BSQ = biggest square

Find the biggest square on a map while avoiding obstacles.
Replace empty cells inside the square with the full character.
```

## Main idea

```text
For each empty cell, calculate the size of the biggest square
ending at this cell.
```

## Header

Example:

```text
9 . o x
```

Meaning:

```text
rows  = 9
empty = '.'
obs   = 'o'
full  = 'x'
```

Important:

```c
char sep1;
char sep2;
char sep3;
char end;

if (fscanf(file, "%d%c%c%c%c%c%c%c",
        &map->rows,
        &sep1,
        &map->empty,
        &sep2,
        &map->obs,
        &sep3,
        &map->full,
        &end) != 8)
    return (0);

if (sep1 != ' ' || sep2 != ' ' || sep3 != ' ')
    return (0);
if (end != '\n')
    return (0);
```

Why:

```text
%c reads every character, including spaces and '\n'.

Reading the separators validates the exact header format.
The final '\n' must be consumed before the first getline call.
```

## Map validation

```text
rows > 0
empty, obs and full are different
all lines have same length
each line ends with '\n'
only empty or obs characters in the map
no extra lines after the map
```

On error:

```c
fputs("map error\n", stderr);
```

## DP formula

```text
obstacle -> 0

empty -> min(top, left, diagonal) + 1
```

## Compact DP

```text
dp[col]     = top
dp[col - 1] = left
prev        = diagonal
save        = old top
```

Core logic:

```c
save = dp[col];

if (map->grid[row - 1][col - 1] == map->obs)
    dp[col] = 0;
else
    dp[col] = min3(dp[col], dp[col - 1], prev) + 1;

prev = save;
```

## Tie-break

```text
If several biggest squares exist:
choose the top-most one,
then the left-most one.
```

Because we scan:

```text
top to bottom
left to right
```

Update only if strictly bigger:

```c
if (dp[col] > bestSize)
```

Not:

```c
if (dp[col] >= bestSize)
```

## Fill square

```text
startRow = bestRow - bestSize + 1
startCol = bestCol - bestSize + 1
```

Fill from:

```text
startRow to bestRow
startCol to bestCol
```

with:

```text
map->full
```

## Heart of the task

```text
BSQ is map parsing + dynamic programming.
```

## Remember

```text
Use getline to read map lines.
getline includes '\n'.
real width = len - 1.

Use fputs, not printf/write/fputc.

Read and validate the three spaces and the final '\n' explicitly.
Do not leave the header newline unread before getline.
```

## Files to implement

```text
*.c
*.h
```
This repository keeps the complete solution in `main.c`.
Splitting it into `bsq.c` and `bsq.h` is optional.