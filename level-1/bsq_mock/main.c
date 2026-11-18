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
	int		num_of_line;
	char	empty_char;
	char	obs_char;
	char	full_char;
	char	**grid;
	int		line_length;
	int		largest_area;
	t_point	largest_top_left;
	t_point	largest_bottom_right;
}			t_map;

void	free_grid(char **grid, int lines)
{
	int	i;

	i = 0;
	// x! need to check grid = null . free(null) ok, but grid[i] will segfault
	if (!grid)
		return ;
	while (i < lines)
	{
		free(grid[i]);
		// x! no need to set grid[i] = NULL;
		i++;
	}
	free(grid);
}

int	check_printable(char c)
{
	if (c >= 33 && c <= 126)
		return (0);
	return (1);
}

int	check_chars(t_map *map)
{
	// 1.  check printable
	if (check_printable(map->empty_char) || check_printable(map->obs_char)
		|| check_printable(map->full_char))
		return (1);
	// 2. check duplicated
	if (map->empty_char == map->obs_char || map->empty_char == map->full_char
		|| map->obs_char == map->full_char)
		return (1);
	return (0);
}

// X! didn't check nread, also return ssize_t instead
// void	strip_linebreak(char *line, ssize_t nread)
// {
// 	if (line[nread - 1] == '\n')
// 		line[nread - 1] = '\0';
// }

ssize_t	strip_linebreak(char *line, ssize_t nread)
{
	if (nread > 0 && line[nread - 1] == '\n')
	{
		line[nread - 1] = '\0';
		return (nread - 1);
	}
	return (nread);
}

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

int	check_allow_chars(char *line, t_map *map, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!(line[i] == map->empty_char || line[i] == map->obs_char))
			return (1);
		i++;
	}
	return (0);
}

int	construct_map(FILE *stream, t_map *map)
{
	char	*line;
	char	*first_line;
	size_t	size;
	ssize_t	nread;
	int		args_matched;
	int		len;
	int		row;

	size = 0;
	line = NULL;
	first_line = NULL;
	// try to scan first as fscanf takes in stream rather then char *
	args_matched = fscanf(stream, "%d %c %c %c", &map->num_of_line,
			&map->empty_char, &map->obs_char, &map->full_char);
	if (args_matched != 4 || map->num_of_line <= 0 || check_chars(map))
		return (1);
	// try to get rid of the \n on the first scanning line
	if ((nread = getline(&first_line, &size, stream)) != -1)
	{
		printf("Retrieved first line %s of nread length %zd:\n", first_line,
			nread);
	}
	else
		return (1);
	// start to read real lines
	// the buffer is null-terminated, and includes the \n (if one was found)
	// on sucess , return the number of chars read,
	// including delimiter like \n,b
	// but not including the terminating null byte(\0)
	// -1 at either end of file or on error
	map->grid = calloc(map->num_of_line, sizeof(char *));
	if (map->grid == NULL)
	{
		fprintf(stderr, "calloc failed\n");
		return (1);
	}
	nread = getline(&first_line, &size, stream);
	strip_linebreak(first_line, nread);
	len = str_len(first_line);
	map->grid[0] = calloc(len, sizeof(char));
	for (int i = 0; i < len; i++)
		map->grid[0][i] = first_line[i];
	row = 1;
	while ((nread = getline(&line, &size, stream)) != -1)
	{
		// check and stripe line break
		strip_linebreak(line, nread);
		// check same length
		if (str_len(line) != len)
		{
			fprintf(stderr, "map error\n");
			free_grid(map->grid, row);
			return (1);
		}
		// check only chars allowed
		if (check_allow_chars(line, map, len) == 1)
		{
			fprintf(stderr, "map error\n");
			free_grid(map->grid, row);
			return (1);
		}
		map->grid[row] = calloc(len, sizeof(char));
		for (int i = 0; i < len; i++)
			map->grid[row][i] = line[i];
		row++;
		printf("Retrieved first line %s of nread length %zd:\n", first_line,
			nread);
	}
	printf(" %d %d %d \n", map->num_of_line, row, len);
	if (!map->grid || map->num_of_line != row)
	{
		fprintf(stderr, "map error\n");
		free_grid(map->grid, row);
		return (1);
	}
	map->line_length = len;
	free(line);
	free(first_line);
	return (0);
}

int	min3(int a, int b, int c)
{
	int	m;

	m = a;
	if (b < m)
		m = b;
	if (c < m)
		m = c;
	return (m);
}

void	update_best(int i, int j, int side, t_map *map)
{
	if (side * side > map->largest_area)
	{
		map->largest_area = side * side;
		map->largest_bottom_right.x = i;
		map->largest_bottom_right.y = j;
		map->largest_top_left.x = i - side + 1;
		map->largest_top_left.y = j - side + 1;
	}
}

void	fill_row(int i, int *prev_row, int *curr_row, t_map *map)
{
	int	side;
	int	j;

	side = 0;
	j = 0;
	while (j < map->line_length)
	{
		if (map->grid[i][j] == map->obs_char)
			side = 0;
		else if (i == 0 || j == 0)
			side = 1;
		else
			side = 1 + min3(prev_row[j - 1], prev_row[j], curr_row[j - 1]);
		curr_row[j] = side;
		update_best(i, j, side, map);
		j++;
	}
}

void	find_biggest_square(t_map *map)
{
	int	*prev_row;
	int	*curr_row;
	int	*tmp;

	// for each cell, i try to look at left , up, left-giagonal,
	// find the smallest one as side
	prev_row = calloc(map->line_length, sizeof(int));
	curr_row = calloc(map->line_length, sizeof(int));
	map->largest_area = 0;
	for (int line_idx = 0; line_idx < map->num_of_line; line_idx++)
	{
		// curent map cell should be filled with the largest side it can have
		fill_row(line_idx, prev_row, curr_row, map);
		tmp = prev_row;
		prev_row = curr_row;
		curr_row = tmp;
	}
	free(prev_row);
	free(curr_row);
}

void	replace_w_full_chars(t_map *map)
{
	// printf("%d %d %d %d \n", map->largest_top_left.x,
	// map->largest_top_left.y,
	// 	map->largest_bottom_right.x, map->largest_bottom_right.y);
	if (map->largest_area == 0)
		return ;
	for (int i = map->largest_top_left.x; i <= map->largest_bottom_right.x; i++)
	{
		for (int j = map->largest_top_left.y; j <= map->largest_bottom_right.y; j++)
			map->grid[i][j] = map->full_char;
	}
}

void	print_map(t_map *map)
{
	for (int i = 0; i < map->num_of_line; i++)
	{
		fprintf(stdout, map->grid[i]);
		fputs("\n", stdout);
	}
}

int	try2solve(FILE *stream)
{
	t_map	map;

	// X! need to initialise
	map = (t_map){0};
	// x! as long as map can be construct , i can start to solve it ?
	if (construct_map(stream, &map) == 1)
	{
		fprintf(stderr, "map error\n");
		return (1);
	}
	find_biggest_square(&map);
	replace_w_full_chars(&map);
	print_map(&map);
	free_grid(map.grid, map.num_of_line);
	return (0);
}

int	main(int ac, char **av)
{
	FILE *stream;
	if (ac == 1)
	{
		stream = stdin;
		if (try2solve(stream) == 1)
			return (1);
	}
	else
	{
		for (int i = 1; i < ac; i++)
		{
			stream = fopen(av[i], "r");
			// open file check
			if (stream == NULL)
				fprintf(stderr, "map error\n");
			// check -1
			else
			{
				try2solve(stream);
				fclose(stream);
			}
		}
	}
}