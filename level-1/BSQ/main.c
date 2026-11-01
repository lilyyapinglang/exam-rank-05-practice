#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct point
{
	int		x;
	int		y;
}			t_point;
typedef struct map
{
	int		num_of_lines;
	char	empty_ch;
	char	obs_ch;
	char	full_ch;
	char	**grid;
	int		biggest_area;
	t_point	top_left;
	t_point	bottom_right;
}			t_map;

int	get_biggest_area_with_top_left(t_map *map, int i, int j)
{
	t_point	top_left;
	int		area;

	top_left.x = i;
	top_left.y = j;
	area = 1;
	// go right first and then go down
	while (i < map->num_of_lines)
	{
		while (map->grid[i + 1] != map->obs_ch || map->grid[i + 1] != '\n')
		// i continue go right until obstackes
		{
			area++;
		}
		else
		{ // i go down
		}
		i++;
	}
}

void	find_biggest_square(t_map *map)
{
	int	j;
	int	biggest_from_this_point;

	j = 0;
	for (int i = 0; i < map->num_of_lines; i++)
	{
		while (map->grid[i][j])
		{
			// set start point
			biggest_from_this_point = get_biggest_area_with_top_left(map, i, j);
			if (biggest_from_this_point > map->biggest_area)
			{
				map->top_left.x = i;
				map->top_left.y = j;
				map->biggest_area = biggest_from_this_point;
				// map->bottom_right?
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	if (ac == 1)
	{
		// READ FROM STDIN
	}
	// can read multiple map.txt inputs
	char *file_path = av[1];

	FILE *stream = fopen(file_path, "r");
	/* Upon successful completion fopen(), fdopen(),
	and freopen() return a FILE pointer.  Otherwise,
	NULL is returned and errno is set to indicate the error.
	*/
	if (stream == NULL)
	{
		perror("fopen");
		return (-1);
	}
	char *line = NULL;
	ssize_t nread = 0;
	size_t size = 0;
	t_map test = {0};

	int a = fscanf(stream, "%d %c %c %c \n", &test.num_of_lines, &test.empty_ch,
			&test.obs_ch, &test.full_ch);
	printf("a is  %d:\n", a);
	// split by space
	/*
	int fscanf(FILE *restrict stream,
					const char *restrict format, ...);

	*/
	test.grid = malloc(test.num_of_lines * sizeof(char *));
	if (!test.grid)
		return (-1);
	int line_number = 0;
	printf("%d\n", test.num_of_lines);
	while (((nread = getline(&line, &size, stream)) != -1)
		&& line_number < test.num_of_lines)
	{
		printf("Retrieved line of length %zd:\n", nread);
		fwrite(line, nread, 1, stdout);
		test.grid[line_number] = malloc(nread + 1);
		if (!test.grid[line_number])
			return (-1);
		for (int i = 0; i < nread; i++)
		{
			test.grid[line_number][i] = line[i];
			i++;
		}
		// fwrite(line, nread, 1, stdout);
		line_number++;
	}
	// algo part, calcualte the biggest square possible
	// just need a top-left coordiante and bottem-right coordiante,
	// 2 points to calculate area
	find_biggest_square(&test);
	fill(&test); //
	// free grid
	free(line);
	fclose(stream);
}