#include "bsq.h"

static void	initMap(tMap *map)
{
	map->rows = 0;
	map->cols = 0;
	map->empty = 0;
	map->obs = 0;
	map->full = 0;
	map->grid = NULL;
}

static int	processMap(FILE *file)
{
	tMap	map;

	initMap(&map);
	if (readMap(file, &map) == 0)
	{
		fputs("map error\n", stderr);
		freeMap(&map);
		return (1);
	}
	solveMap(&map);
	printMap(&map);
	freeMap(&map);
	return (0);
}

int	main(int argc, char **argv)
{
	FILE	*file;
	int		i;

	if (argc == 1)
		return (processMap(stdin));
	i = 1;
	while (i < argc)
	{
		file = fopen(argv[i], "r");
		if (file == NULL)
			fputs("map error\n", stderr);
		else
		{
			processMap(file);
			fclose(file);
		}
		if (i + 1 < argc)
			fputs("\n", stdout);
		i++;
	}
	return (0);
}