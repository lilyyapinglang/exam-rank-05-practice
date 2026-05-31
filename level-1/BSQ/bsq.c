#include "bsq.h"

static int	isPrint(char c)
{
	return (c >= 33 && c <= 126);
}

static int	isDigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	skipSpaces(char *line, int pos)
{
	while (line[pos] == ' ')
		pos++;
	return (pos);
}

static int	parseHead(char *line, tMap *map)
{
	int	pos;
	int	num;

	pos = 0;
	num = 0;
	if (!isDigit(line[pos]))
		return (0);
	while (isDigit(line[pos]))
	{
		num = num * 10 + line[pos] - '0';
		pos++;
	}
	if (num <= 0)
		return (0);
	map->rows = num;
	pos = skipSpaces(line, pos);
	if (!isPrint(line[pos]))
		return (0);
	map->empty = line[pos++];
	pos = skipSpaces(line, pos);
	if (!isPrint(line[pos]))
		return (0);
	map->obs = line[pos++];
	pos = skipSpaces(line, pos);
	if (!isPrint(line[pos]))
		return (0);
	map->full = line[pos++];
	pos = skipSpaces(line, pos);
	if (line[pos] != '\n' && line[pos] != '\0')
		return (0);
	if (map->empty == map->obs || map->empty == map->full
		|| map->obs == map->full)
		return (0);
	return (1);
}

static int	saveLine(tMap *map, char *line, int row, int len)
{
	int	col;

	if (len <= 1 || line[len - 1] != '\n')
		return (0);
	if (row == 0)
	{
		map->cols = len - 1;
		if (map->cols <= 0)
			return (0);
	}
	else if (len - 1 != map->cols)
		return (0);
	map->grid[row] = calloc(map->cols + 1, sizeof(char));
	if (map->grid[row] == NULL)
		return (0);
	col = 0;
	while (col < map->cols)
	{
		if (line[col] != map->empty && line[col] != map->obs)
			return (0);
		map->grid[row][col] = line[col];
		col++;
	}
	return (1);
}

int	readMap(FILE *file, tMap *map)
{
	char	*line;
	size_t	size;
	ssize_t	len;
	int		row;

	line = NULL;
	size = 0;
	len = getline(&line, &size, file);
	if (len == -1 || parseHead(line, map) == 0)
	{
		free(line);
		return (0);
	}
	map->grid = calloc(map->rows, sizeof(char *));
	if (map->grid == NULL)
	{
		free(line);
		return (0);
	}
	row = 0;
	while (row < map->rows)
	{
		len = getline(&line, &size, file);
		if (len == -1 || saveLine(map, line, row, len) == 0)
		{
			free(line);
			return (0);
		}
		row++;
	}
	len = getline(&line, &size, file);
	free(line);
	if (len != -1)
		return (0);
	return (1);
}

static int	min3(int a, int b, int c)
{
	int	min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

static void	fillSquare(tMap *map, int bestRow, int bestCol, int bestSize)
{
	int	row;
	int	col;

	row = bestRow - bestSize + 1;
	while (row <= bestRow)
	{
		col = bestCol - bestSize + 1;
		while (col <= bestCol)
		{
			map->grid[row][col] = map->full;
			col++;
		}
		row++;
	}
}

int	solveMap(tMap *map)
{
	int	*dp;
	int	row;
	int	col;
	int	prev;
	int	save;
	int	bestSize;
	int	bestRow;
	int	bestCol;

	dp = calloc(map->cols + 1, sizeof(int));
	if (dp == NULL)
		return (0);
	bestSize = 0;
	bestRow = 0;
	bestCol = 0;
	row = 1;
	while (row <= map->rows)
	{
		prev = 0;
		col = 1;
		while (col <= map->cols)
		{
			save = dp[col];
			if (map->grid[row - 1][col - 1] == map->obs)
				dp[col] = 0;
			else
			{
				dp[col] = min3(dp[col], dp[col - 1], prev) + 1;
				if (dp[col] > bestSize)
				{
					bestSize = dp[col];
					bestRow = row - 1;
					bestCol = col - 1;
				}
			}
			prev = save;
			col++;
		}
		row++;
	}
	free(dp);
	if (bestSize > 0)
		fillSquare(map, bestRow, bestCol, bestSize);
	return (1);
}

void	printMap(tMap *map)
{
	int	row;

	row = 0;
	while (row < map->rows)
	{
		fputs(map->grid[row], stdout);
		fputs("\n", stdout);
		row++;
	}
}

void	freeMap(tMap *map)
{
	int	row;

	if (map->grid == NULL)
		return ;
	row = 0;
	while (row < map->rows)
	{
		free(map->grid[row]);
		row++;
	}
	free(map->grid);
	map->grid = NULL;
}