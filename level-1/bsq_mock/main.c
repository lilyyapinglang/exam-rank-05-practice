#include <stdio.h>
#include <unistd.h>

typedef struct map
{
	int		num_of_line;
	char	empty_char;
	char	obs_char;
	char	full_char;
	char	**grid;
	int		line_length;
}			t_map;

// int is_printable();

int	check_chars(t_map *map)
{
	// 1.  check printable
	// 2. check duplicated
	return (0);
}

void	strip_linebreak(char *line, ssize_t nread)
{
	if (line[nread - 1] == '\n')
		line[nread - 1] == '\0';
}

int	contruct_map(FILE *stream, t_map *map)
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
	// try to scan first as fscanf takes in stream rather then char *
	args_matched = fscanf(stream, "%d %c %c %c", &map->num_of_line,
			&map->empty_char, &map->obs_char, &map->full_char);
	if (args_matched != 4 || map->num_of_line <= 0 || check_chars(&map))
	{
		fprintf(stderr, "map error\n");
		return (1);
	}
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
	len = strlen(first_line);
	map->grid[0] = calloc(len, sizeof(char));
	for (int i = 0; i < len; i++)
		map->grid[0][i] = first_line[i];
	row = 1;
	while ((nread = getline(&line, &size, stream)) != -1)
	{
		// check and stripe line break
		strip_linebreak(line, nread);
		// check same length
		if (strlen(line) != len)
		{
			fprintf(stderr, "map error\n");
			// free grid
			return (1);
		}
		// check only chars allowed
		if (check_allow_chars(line, *map) == 1)
		{
			fprintf(stderr, "map error\n");
			// free grid
			return (1);
		}
		map->grid[row] = calloc(len, sizeof(char));
		for (int i = 0; i < len; i++)
			map->grid[row][i] = line[i];
		printf("Retrieved first line %s of nread length %zd:\n", first_line,
			nread);
	}
	if (!map->grid || map->num_of_line != row)
	{
		fprintf(stderr, "map error\n");
		// free grid
		return (1);
	}
	map->line_length = len;
	free(line);
}

void	find_biggest_square(t_map *map)
{
	// for each cell, i try to look at left , up, left-giagonal
	//?
}

int	try2solve(FILE *stream)
{
	t_map	map;

	construct_map(stream, &map);
	find_biggest_square(&map);
	replace_w_full_chars(&map);
	print_map(&map);
}

int	main(int ac, char **av)
{
	FILE *stream;
	if (ac == 1)
	{
		stream = stdin;
		if (try2solve(stream) == 1)
			return ;
	}
	else
	{
		for (int i = 1; i < ac; i++)
		{
			stream = fopen(av[i], "r");
			// open file check
			if (stream == NULL)
			{
				fprintf(stderr, "map error\n");
				break ;
			}
			// check -1
			if (try2solve(stream) == 1)
				fprintf(stderr, "map error\n");
			fclose(stream);
		}
	}
}