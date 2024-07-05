

#include "cub3d.h"

void	ft_move_up(t_data *d)
{
	double		y;
	double		x;
	double	x_mov;
	double	y_mov;

	x_mov = cos(d->ply.ang) * MOV;
	y_mov = -sin(d->ply.ang) * MOV;
	x = d->ply.x + x_mov;
	y = d->ply.y + y_mov;
	if (d->maps.map[(int)y / CELL][(int)x / CELL] != '1')
	{
		d->ply.x = x;
		d->ply.y = y;
	}
}

void	ft_move_down(t_data *d)
{
	int		y;
	int		x;
	double	x_mov;
	double	y_mov;

	x_mov = cos(d->ply.ang + M_PI) * MOV;
	y_mov = -sin(d->ply.ang + M_PI) * MOV;
	x = d->ply.x + x_mov;
	y = d->ply.y + y_mov;
	if (d->maps.map[y / CELL][x / CELL] != '1')
	{
		d->ply.x = x;
		d->ply.y = y;
	}
}

void	ft_move_left(t_data *d)
{
	int		y;
	int		x;
	double	x_mov;
	double	y_mov;

	x_mov = cos(d->ply.ang + M_PI_2) * MOV;
	y_mov = -sin(d->ply.ang + M_PI_2) * MOV;
	x = d->ply.x + x_mov;
	y = d->ply.y + y_mov;
	if (d->maps.map[y / CELL][x / CELL] != '1')
	{
		d->ply.x = x;
		d->ply.y = y;
	}
}

void	ft_move_right(t_data *d)
{
	int		y;
	int		x;
	double	x_mov;
	double	y_mov;

	x_mov = +cos(d->ply.ang - M_PI_2) * MOV;
	y_mov = -sin(d->ply.ang - M_PI_2) * MOV;
	x = d->ply.x + x_mov;
	y = d->ply.y + y_mov;
	if (d->maps.map[y / CELL][x / CELL] != '1')
	{
		d->ply.x = x;
		d->ply.y = y;
	}
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
