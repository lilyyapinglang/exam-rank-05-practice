#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

// bool	is_valid_map(void)
// {
// }
int	get_area(t_point top_left, t_point bottom_right)
{
	return (bottom_right.x - top_left.x + 1) * (bottom_right.y - top_left.y
		+ 1);
}

int	str_len(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

// i want to get the biggest area from (i,j) with the corresponding bottom-right coordinate
t_area	get_biggest_area_with_top_left(t_map *map, int start_i, int start_j)
{
	int		curr_line_area;
	int		furtherest_obs_index_so_far;
	t_point	curr_line_bottom_right;
	t_area	biggest_area_from_i_j;
	int		curr_j;
	int		curr_i;

	biggest_area_from_i_j.top_left.x = start_i;
	biggest_area_from_i_j.top_left.y = start_j;
	biggest_area_from_i_j.bottom_right.x = start_i;
	biggest_area_from_i_j.bottom_right.y = start_j;
	furtherest_obs_index_so_far = map->line_length;
	curr_line_area = 0;
	biggest_area_from_i_j.area = 0;
	// go right first and then go down
	curr_i = start_i;
	while (curr_i < map->num_of_lines)
	{
		curr_j = start_j;
		while (map->grid[curr_i][curr_j]
			&& map->grid[curr_i][curr_j] != map->obs_ch
			&& map->grid[curr_i][curr_j] != '\n'
			&& curr_j < furtherest_obs_index_so_far)
			// i continue go right until obstackes
			curr_j++;
		// 	curr_line_bottom_right.x = i;
		// 	curr_line_bottom_right.y = curr_j - 1;
		// 	curr_line_area = get_area(biggest_area_from_i_j.top_left,
		// 			curr_line_bottom_right);
		// 	if (curr_line_area > biggest_area_from_i_j.area)
		// 	{
		// 		biggest_area_from_i_j.area = curr_line_area;
		// 		biggest_area_from_i_j.bottom_right = curr_line_bottom_right;
		// 	}
		// 	if (curr_j < furtherest_obs_index_so_far)
		// 		furtherest_obs_index_so_far = curr_j;
		// }
		// 实际能达到的最右边界是 curr_j - 1
		if (curr_j > start_j)
		{
			curr_line_bottom_right.x = curr_i;
			curr_line_bottom_right.y = curr_j - 1;
			curr_line_area = get_area(biggest_area_from_i_j.top_left,
					curr_line_bottom_right);
			if (curr_line_area > biggest_area_from_i_j.area)
			{
				biggest_area_from_i_j.area = curr_line_area;
				biggest_area_from_i_j.bottom_right = curr_line_bottom_right;
			}
			furtherest_obs_index_so_far = curr_j;
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
		while (map->grid[i][j] && map->grid[i][j] != '\n')
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
	j = map->top_left.y;
	printf("\nin replacing, top left : %d, %d ; bottom right: %d, %d \n",
		map->top_left.x, map->top_left.y, map->bottom_right.x,
		map->bottom_right.y);
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
		if (map->grid[i])
		{
			fprintf(stdout, "%s", map->grid[i]);
			i++;
		}
	}
}

int	main(int ac, char **av)
{
	FILE *stream;
	if (ac == 1)
	{
		// READ FROM STDIN
		stream = stdin;
	}
	else
	{
		// can read multiple map.txt inputs
		char *file_path = av[1];

		stream = fopen(file_path, "r");
	}
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
	if (!test.grid) // allocation failed
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
		printf("line is %s\n", line);
		for (int i = 0; i < nread + 1; i++)
		{
			test.grid[line_number][i] = line[i];
			// printf("test.grid[line_number][i] %c\n",
			//	test.grid[line_number][i]);
		}
		// test.grid[line_number][nread] = '\0';
		// printf("test.grid[line_number][nread] %s\n", test.grid[line_number]);
		// fwrite(line, nread, 1, stdout);
		// test.grid[line_number] = line;
		line_number++;
	}
	// printf(errno);
	printf("\ni want to print map\n");

	print_map(&test);
	test.line_length = str_len(test.grid[1]);
	// algo part, calcualte the biggest square possible
	// just need a top-left coordiante and bottem-right coordiante,
	// 2 points to calculate area
	find_biggest_square(&test);
	printf("\ni want to print map before replace \n");
	print_map(&test);          // fprint
	replace_full_chars(&test); // fputs
	// free grid
	printf("\ni want to print map after replace \n");
	print_map(&test); // fprintf
	free(line);
	fclose(stream);
}