#include <stdio.h>
#include <stdlib.h>

typedef struct point
{
	int		x;
	int		y;
}			t_point;

typedef struct area
{
	t_point	top_left;
	t_point	bottom_right;
	int		area;
}			t_area;

typedef struct map
{
	int		num_of_lines;
	char	empty_ch;
	char	obs_ch;
	char	full_ch;
	char	**grid;
	int		line_length;
	int		biggest_area;
	t_point	top_left;
	t_point	bottom_right;
}			t_map;

void	free_grid(char **grid, int num_of_lines)
{
	int	i;

	i = 0;
	if (!grid)
		return ;
	while (i < num_of_lines)
	{
		free(grid[i]);
		i++;
	}
	free(grid);
}

int	is_printable(char a)
{
	if (a >= 33 && a <= 126)
		return (1);
	else
		return (0);
}

int	check_args(t_map *map)
{
	// check if char is printable. 33-126
	if (!(is_printable(map->empty_ch) && is_printable(map->full_ch)
			&& is_printable(map->obs_ch)))
		return (0);
	// check if two chars identical
	if (map->empty_ch == map->full_ch || map->full_ch == map->obs_ch
		|| map->obs_ch == map->empty_ch)
		return (0);
	return (1);
}

int	is_valid_cell(t_map *map, char c)
{
	return (c == map->empty_ch || c == map->obs_ch);
}

ssize_t	strip_newline(char *line, ssize_t nread)
{
	if (nread > 0 && line[nread - 1] == '\n')
	{
		line[nread - 1] = '\0';
		return (nread - 1);
	}
	return (nread);
}

// i want to get the biggest area from (i,j) with the corresponding bottom-right coordinate
t_area	get_biggest_area_with_top_left(t_map *map, int start_i, int start_j)
{
	t_area	biggest_area_from_i_j;
	int		curr_j;
	int		curr_i;
	int		width;
	int		height;
	int		side;
	int		furtherest_obs_index_so_far;

	biggest_area_from_i_j.bottom_right.x = start_i;
	biggest_area_from_i_j.bottom_right.y = start_j;
	furtherest_obs_index_so_far = map->line_length;
	biggest_area_from_i_j.area = 0;
	// go right first and then go down
	curr_i = start_i;
	while (curr_i < map->num_of_lines)
	{
		curr_j = start_j;
		while (map->grid[curr_i][curr_j]
			&& map->grid[curr_i][curr_j] != map->obs_ch
			&& curr_j < furtherest_obs_index_so_far)
			// i continue go right until obstackes
			curr_j++;
		if (curr_j > start_j)
		{
			furtherest_obs_index_so_far = curr_j;
			width = curr_j - start_j;
			height = curr_i - start_i + 1;
			side = (width < height) ? width : height;
			if (side * side > biggest_area_from_i_j.area)
			{
				biggest_area_from_i_j.area = side * side;
				biggest_area_from_i_j.bottom_right.x = start_i + side - 1;
				biggest_area_from_i_j.bottom_right.y = start_j + side - 1;
				// furtherest_obs_index_so_far = curr_j;
			}
			if (height >= width)
				break ;
		}
		else
		{
			// 如果当前行的起点直接就是障碍物，下面几行组成的矩形也无法超越这里
			break ;
		}
		curr_i++;
	}
	return (biggest_area_from_i_j);
}

void	find_biggest_square(t_map *map)
{
	int		j;
	t_area	biggest_from_this_point;

	j = 0;
	for (int i = 0; i < map->num_of_lines; i++)
	{
		j = 0; // every new line should start with j=0;
		while (map->grid[i][j])
		{
			// set start point
			biggest_from_this_point = get_biggest_area_with_top_left(map, i, j);
			if (biggest_from_this_point.area > map->biggest_area)
			{
				map->top_left.x = i;
				map->top_left.y = j;
				map->biggest_area = biggest_from_this_point.area;
				map->bottom_right = biggest_from_this_point.bottom_right;
			}
			j++;
		}
	}
}

void	replace_full_chars(t_map *map)
{
	int	i;
	int	j;

	//  int fputs(const char *restrict s, FILE *restrict stream);
	i = map->top_left.x;
	if (map->biggest_area == 0)
		return ;
	while (i <= map->bottom_right.x)
	{
		j = map->top_left.y;
		while (j <= map->bottom_right.y)
		{
			map->grid[i][j] = map->full_ch;
			j++;
		}
		i++;
	}
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->num_of_lines)
	{
		fputs(map->grid[i], stdout);
		fputc('\n', stdout);
		i++;
	}
}

// store line after validation into grid[idx]. return 1 on success.
int	store_line(t_map *map, int idx, char *line, ssize_t nread)
{
	ssize_t	len;
	ssize_t	i;

	// line length is set at the first line,and then compared with each line after
	len = strip_newline(line, nread);
	if (len == 0)
		return (0); // empty line is not valid
	if (idx > 0 && len != map->line_length)
		return (0); // not the same as the len of 1st line
	i = 0;
	while (i < len)
	{
		if (!is_valid_cell(map, line[i]))
			return (0);
		i++;
	}
	map->grid[idx] = malloc(len + 1);
	if (!map->grid[idx])
		return (0);
	i = 0;
	while (i < len)
	{
		map->grid[idx][i] = line[i];
		i++;
	}
	map->grid[idx][len] = '\0';
	map->line_length = len;
	return (1);
}

// handle all errors
int	read_map(FILE *stream, t_map *map)
{
	char	*line;
	size_t	size;
	ssize_t	nread;
	int		n;

	line = NULL;
	size = 0;
	if (fscanf(stream, "%d %c %c %c", &map->num_of_lines, &map->empty_ch,
			&map->obs_ch, &map->full_ch) != 4 || map->num_of_lines <= 0
		|| !check_args(map))
		return (0);
	// get rid of the \n at the end of the line
	nread = getline(&line, &size, stream);
	map->grid = calloc(map->num_of_lines, sizeof(char *));
	n = 0;
	while (map->grid && n < map->num_of_lines && (nread = getline(&line, &size,
				stream)) != -1 && store_line(map, n, line, nread))
		n++;
	// if lines of not enough or the files have extra lines, error
	if (!map->grid || n != map->num_of_lines || getline(&line, &size, stream) !=
		-1)
	{
		free_grid(map->grid, map->num_of_lines);
		map->grid = NULL;
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

int	solve(FILE *stream)
{
	t_map	map;

	map = (t_map){0};
	if (!read_map(stream, &map))
	{
		fprintf(stderr, "map error\n");
		return (1);
	}
	find_biggest_square(&map);
	replace_full_chars(&map); // fputs
	print_map(&map);          // fprintf
	free_grid(map.grid, map.num_of_lines);
	return (0);
}

int	main(int ac, char **av)
{
	FILE	*stream;
	int		i;

	if (ac == 1)
		// READ FROM STDIN
		return (solve(stdin));
	i = 1;
	while (i < ac)
	{
		if (i > 1)
			fputc('\n', stdout);
		stream = fopen(av[i], "r");
		if (!stream)
			fprintf(stderr, "map error\n");
		else
		{
			solve(stream);
			fclose(stream);
		}
		i++;
	}
	return (0);
}

/* Upon successful completion fopen(), fdopen(),
and	freopen(void) return a FILE pointer.  Otherwise,
NULL is returned and errno is set to indicate the error.
*/
