#ifndef BSQH
# define BSQH

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>

typedef struct sMap
{
	int		rows;
	int		cols;
	char	empty;
	char	obs;
	char	full;
	char	**grid;
}	tMap;

int		readMap(FILE *file, tMap *map);
int		solveMap(tMap *map);
void	printMap(tMap *map);
void	freeMap(tMap *map);

#endif