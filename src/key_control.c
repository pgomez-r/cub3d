

#include "cub3d.h"

void	ft_move_up(t_data *d)
{
	int	y;
	int	x;

	y = d->ply.y;
	x = d->ply.x;
	if (d->maps.map[((y) - MOV) / CELL][x / CELL] != '1'
		&& d->maps.map[((y) - MOV) / CELL][(x + 12) / CELL] != '1')
		d->ply.y -= MOV;
}

void	ft_move_down(t_data *d)
{
	int	y;
	int	x;

	y = d->ply.y;
	x = d->ply.x;
	if (d->maps.map[((y + 12) + MOV) / CELL][(x + 12) / CELL] != '1'
		&& d->maps.map[((y + 12) + MOV) / CELL][x / CELL] != '1')
		d->ply.y += MOV;
}

void	ft_move_left(t_data *d)
{
	int	y;
	int	x;

	y = d->ply.y;
	x = d->ply.x;
	if (d->maps.map[(y) / CELL][(x - MOV) / CELL] != '1'
		&& d->maps.map[(y + 12) / CELL][(x - MOV) / CELL] != '1')
		d->ply.x -= MOV;
}

void	ft_move_right(t_data *d)
{
	int	y;
	int	x;

	y = d->ply.y;
	x = d->ply.x;
	if (d->maps.map[y / CELL][((x + 12) + MOV) / CELL] != '1'
		&& d->maps.map[(y + 12) / CELL][((x + 12) + MOV) / CELL] != '1')
		d->ply.x += MOV;
}

void	ft_key_control(t_data *d)
{
	if (mlx_is_key_down(d->game, MLX_KEY_ESCAPE))
	{
		d->exit_code = -1;
		mlx_close_window(d->game);
	}
	if (mlx_is_key_down(d->game, MLX_KEY_W))
		ft_move_up(d);
	if (mlx_is_key_down(d->game, MLX_KEY_S))
		ft_move_down(d);
	if (mlx_is_key_down(d->game, MLX_KEY_A))
		ft_move_left(d);
	if (mlx_is_key_down(d->game, MLX_KEY_D))
		ft_move_right(d);
	if (mlx_is_key_down(d->game, MLX_KEY_LEFT))
	{
		d->ply.ang += (M_PI / 180);
		if (d->ply.ang >= 2 * M_PI)
			d->ply.ang -= 2 * M_PI;
	}
	if (mlx_is_key_down(d->game, MLX_KEY_RIGHT))
	{
		d->ply.ang -= (M_PI / 180);
		if (d->ply.ang < 0)
			d->ply.ang += 2 * M_PI;
	}
}
