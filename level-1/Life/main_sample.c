#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_game
{
	char	**grid;
	int		width;
	int		height;
	int		iterations;
}			t_game;

// free row first, then the **pointer.
static void	free_grid(char **g, int rows)
{
	if (!g)
		return ;
	for (int i = 0; i < rows; i++)
		free(g[i]);
	free(g);
}

// create a w*h grid ** and fill with ' '
static char	**alloc_grid(int w, int h)
{
	char	**g;

	g = calloc(h, sizeof(char *));
	if (!g)
		return (NULL);
	for (int r = 0; r < h; r++)
	{
		g[r] = malloc(w);
		// if allocation fail for any row, free gird until r
		if (!g[r])
		{
			free_grid(g, r);
			return (NULL);
		}
		// fill this row with space
		for (int c = 0; c < w; c++)
			g[r][c] = ' ';
	}
	return (g);
}

// dra, aka add 'o'
static void	draw_init_board(t_game *g)
{
	int		row;
	char	c;
	int		col;
	int		pen_status;

	row = 0, col = 0, pen_status = 0;
	// i read from standard input , one char by one char
	while (read(STDIN_FILENO, &c, 1) > 0)
	{
		if (c == 'x')
			pen_status = !pen_status;
		else if (c == 'w' && row > 0)
			row--;
		else if (c == 's' && row < g->height - 1)
			row++;
		else if (c == 'a' && col > 0)
			col--;
		else if (c == 'd' && col < g->width - 1)
			col++;
		if (pen_status)
			g->grid[row][col] = 'O';
	}
}

static int	count_alive_neighbors(t_game *game, int cell_row, int cell_col)
{
	int	neighbor_row;
	int	neighbor_col;

	int alive_count = 0; // 活着的邻居数量，最后返回它
	// row_offset: 相对中心格子的行偏移，取 -1(上一行)、0(同一行)、+1(下一行)
	for (int row_offset = -1; row_offset <= 1; row_offset++)
	{
		// col_offset: 相对中心格子的列偏移，取 -1(左边)、0(同一列)、+1(右边)
		for (int col_offset = -1; col_offset <= 1; col_offset++)
		{
			// 1) 跳过中心格子本身：两个偏移都是 0 就是它自己，不是邻居
			if (row_offset == 0 && col_offset == 0)
				continue ;
			// 2) 算出这个邻居的真实坐标
			neighbor_row = cell_row + row_offset;
			neighbor_col = cell_col + col_offset;
			// 3) 检查邻居是否在棋盘范围内（边缘格子的邻居可能超出棋盘）
			//    超出范围就跳过，不能去读，否则会越界访问（崩溃）
			if (neighbor_row < 0 || neighbor_row >= game->height)
				continue ;
			if (neighbor_col < 0 || neighbor_col >= game->width)
				continue ;
			// 4) 邻居在棋盘内，如果它是活的就计数 +1
			if (game->grid[neighbor_row][neighbor_col] == 'O')
				alive_count++;
		}
	}
	return (alive_count);
}

// Returns 0 on success, 1 if memory allocation failed.
static int	is_compute_next_generation_failed(t_game *game)
{
	char	**next_grid;
	int		alive_neighbors;
	int		is_alive;

	// 1) Make a new blank board (all cells ' ' = dead).
	//    We only write 'O' into it for cells that survive or are born.
	next_grid = alloc_grid(game->width, game->height);
	if (!next_grid)
		return (1);
	// 2) Visit every cell of the CURRENT board.
	for (int row = 0; row < game->height; row++)
	{
		for (int col = 0; col < game->width; col++)
		{
			// How many of the 8 neighbors are alive (in the current board)?
			alive_neighbors = count_alive_neighbors(game, row, col);
			// Is this cell alive right now?
			is_alive = (game->grid[row][col] == 'O');
			// 3) Apply the rules. Dead cells need no code: the next
			//    board is already filled with ' ', so they stay dead.
			if (is_alive && (alive_neighbors == 2 || alive_neighbors == 3))
				next_grid[row][col] = 'O'; // survives
			else if (!is_alive && alive_neighbors == 3)
				next_grid[row][col] = 'O'; // is born
		}
	}
	// 4) The old board is no longer needed. Free it,
	//    then make the next board the current one.
	free_grid(game->grid, game->height);
	game->grid = next_grid;
	return (0);
}

int	main(int ac, char **av)
{
	t_game g;

	if (ac != 4)
		return (1);
	g.width = atoi(av[1]);
	g.height = atoi(av[2]);
	g.iterations = atoi(av[3]);
	if (g.width <= 0 || g.height <= 0 || g.iterations < 0)
		return (1);
	g.grid = alloc_grid(g.width, g.height);
	if (!g.grid)
		return (1);
	// i got a grid of ' '
	// read char by char to draw the bord
	draw_init_board(&g);

	// iterations
	for (int i = 0; i < g.iterations; i++)
		if (is_compute_next_generation_failed(&g))
			return (1);

	// print grid
	for (int r = 0; r < g.height; r++)
	{
		for (int c = 0; c < g.width; c++)
			putchar(g.grid[r][c]);
		putchar('\n');
	}
	// free
	free_grid(g.grid, g.height);
	return (0);
}