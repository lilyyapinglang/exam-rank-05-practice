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
	int		line_length;
	int		biggest_area;
	t_point	top_left;
	t_point	bottom_right;
}			t_map;

/*
	not every char ** ends with NULL, unless we built that way
	so it is necessayr to pass num_of_lines here.
*/
void	free_grid(char **grid, int num_of_lines)
{
	int	i;

	i = 0;
	// grid is array of pointers
	// if grid=null, nothing to free
	// free(NULL) is ok, but  grid[i] deference will give segmentfault
	// so it is neceeary to check here.
	if (!grid)
		return ;
	while (i < num_of_lines)
	{
		free(grid[i]);
		i++;
	}
	// free the memory that stores the array of line pointers.
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

void	replace_full_chars(t_map *map)
{
	int	i;
	int	j;

	//  int fputs(const char *restrict s, FILE *restrict stream);
	// if top_left and bottom_right are all o,
	// it will be changed to x.so need to check!
	if (map->biggest_area == 0)
		return ;
	i = map->top_left.x;
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
		fputs("\n", stdout);
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
	// the line after line 0 is not the same as the len of 1st line
	if (idx > 0 && len != map->line_length)
		return (0);
	i = 0;
	// check if line contains invalid chars
	while (i < len)
	{
		if (!is_valid_cell(map, line[i]))
			return (0);
		i++;
	}
	// after check, then I can finally start to store it in my grid
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
	// i only set the line_length at the end?
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
	// to prevent store_line (map]null);
	while (map->grid && n < map->num_of_lines && (nread = getline(&line, &size,
				stream)) != -1 && store_line(map, n, line, nread))
		n++;
	// if lines of not enough or the files have extra lines, error
	// to check if readmap failed.
	if (!map->grid || n != map->num_of_lines || getline(&line, &size, stream) !=
		-1)
	{
		free_grid(map->grid, map->num_of_lines);
		map->grid = NULL; // prevent dangling pointer
		free(line);
		return (0);
	}
	free(line);
	return (1);
}

static int	min3(int a, int b, int c)
{
	int	m;

	m = a;
	if (b < m)
		m = b;
	if (c < m)
		m = c;
	return (m);
}

static void	update_best(t_map *map, int i, int j, int side)
{
	if (side * side > map->biggest_area)
	{
		map->biggest_area = side * side;
		map->top_left.x = i - side + 1;
		map->top_left.y = j - side + 1;
		map->bottom_right.x = i;
		map->bottom_right.y = j;
	}
}

static void	fill_row(t_map *map, int line_idx, int *prev_row, int *curr_row)
{
	int	j;

	j = 0;
	while (j < map->line_length)
	{
		if (map->grid[line_idx][j] == map->obs_ch)
			curr_row[j] = 0;
		else if (line_idx == 0 || j == 0)
			curr_row[j] = 1;
		else
			curr_row[j] = 1 + min3(prev_row[j], curr_row[j - 1], prev_row[j
					- 1]);
		// try to see  if it the new biggesg value
		// curr_row[j] is the largest side length from i,j
		update_best(map, line_idx, j, curr_row[j]);
		j++;
	}
}

void	find_biggest_square(t_map *map)
{
	int	*prev_row;
	int	*curr_row;
	int	*tmp;
	int	line_idx;

	// construct 2 array of int to store, number
	prev_row = calloc(map->line_length, sizeof(int)); // all 0
	curr_row = calloc(map->line_length, sizeof(int)); // all 0
	// if allocation failled, free
	if (!prev_row || !curr_row)
	{
		free(prev_row);
		free(curr_row);
		return ;
	}
	// from line =0;
	line_idx = 0;
	while (line_idx < map->num_of_lines)
	{
		// swap 2 pointers
		// prev row: save result of the prev row
		// curr row : save result of current row
		fill_row(map, line_idx, prev_row, curr_row);
		// 只保留需要的数据，用交换指针代替复制数据。?
		tmp = prev_row; // save the address of the prev first
		prev_row = curr_row;
		// make prev_row ponter to the memory pointed by curr_row;
		curr_row = tmp;
		// make curr_row point to the memory pointed by prev_row.
		line_idx++;
	}
	free(prev_row);
	free(curr_row);
}

int	solve(FILE *stream)
{
	t_map	map;

	map = (t_map){0};
	//	try to contruct a map from the stream
	if (!read_map(stream, &map))
	{
		fprintf(stderr, "map error\n");
		return (1);
	}
	// map successully loaded, algo part
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
		// when supporting multiple maps, result should be seprated by \n
		if (i > 1)
			fputc('\n', stdout);
		stream = fopen(av[i], "r");
		if (!stream)
			// i don't return here because i need to check next file
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
