
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct pen_pos
{
	int			x;
	int			y;
}				t_pen_pos;
typedef struct game
{
	char		**grid;
	int			width;
	int			height;
	int			iterations;
	t_pen_pos	pen_pos;
	int			pen_draw;
}				t_game;

void	change_pen_state(t_game *game)
{
	if (game->pen_draw == 0)
		game->pen_draw = 1;
	else if (game->pen_draw == 1)
		game->pen_draw = 0;
	else
	{
		putchar('!');
		return ;
	}
}

void	draw_init_board(char *cmd, t_game *game)
{
	game->grid = calloc(game->height, sizeof(char *));
	if (!game->grid)
		return ;
	while (cmd)
	{
		if (*cmd == 'x')
			change_pen_state(game);
		else if (*cmd == 'w' && game->pen_pos.x > 0)
			game->pen_pos.x--;
		else if (*cmd == 's' && game->pen_pos.x < game->height - 1)
			game->pen_pos.x++;
		else if (*cmd == 'a' && game->pen_pos.y > 0)
			game->pen_pos.y--;
		else if (*cmd == 'd' && game->pen_pos.y < game->width - 1)
			game->pen_pos.y++;
		else
		{
			putchar('!');
			return ;
		} 
		if (game->pen_draw == 1)
			game->grid[game->pen_pos.x][game->pen_pos.y] = 'O';
		cmd++;
	}
}

void	update(int row_idx, int col_idx, t_game *game)
{
	int num_of_neighers_alive = count_live_neighbros(row_idx, col_idx)
}

void	simulate_game(t_game *game)
{
	int	row_idx;
	int	col_idx;
	int	iter_round;

	row_idx = 0;
	col_idx = 0;
	while (iter_round <= game->iterations)
	{
		row_idx = 0;
		col_idx = 0;
		while (row_idx < game->height)
		{
			while (col_idx < game->width)
			{
				update(game->grid[row_idx][col_idx]);
				col_idx++;
			}
			row_idx++;
		}
		iter_round++;
	}
}

int	main(int ac, char **av)
{
	if (ac != 4)
		return (1);
	int width = atoi(av[1]);
	int height = atoi(av[2]);
	int iterations = atoi(av[3]);

	// ssize_t read(int fildes, void *buf, size_t nbyte);

	char *cmd;
	char buf[20];
	char *tmp;
	size_t nbytes;
	ssize_t bytes_read;
	ssize_t total_bytes_read;

	nbytes = sizeof(buf);

	while ((bytes_read = read(STDIN_FILENO, buf, nbytes)) > 0)
	{
		// append buf to bug
		total_bytes_read += bytes_read;
		tmp = realloc(cmd, total_bytes_read * sizeof(char));

		if (!tmp)
		{
			free(cmd);
			return (1);
		}
		cmd = tmp;
		ssize_t i = 0;
		while (buf[i])
		{
			cmd[total_bytes_read - bytes_read + i] = buf[i];
			i++;
		}
	}

	t_game game;
	game = (t_game){0};
	game.width = width;
	game.height = height;
	game.iterations = iterations;
	draw_init_board(cmd, &game);
	simulate_game(&game);
	// free things
}