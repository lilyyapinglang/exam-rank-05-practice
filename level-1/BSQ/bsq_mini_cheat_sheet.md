    # BSQ — Mini Cheat Sheet

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
fscanf(file, "%d %c %c %c", &map->rows,
    &map->empty, &map->obs, &map->full);
```

Do not use:

```c
"%d%c%c%c"
```

Because `%c` reads spaces too.

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

Header must be read with spaces:
"%d %c %c %c"
```

## Files to implement

```text
main.c
bsq.c
bsq.h
```
