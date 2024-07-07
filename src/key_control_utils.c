

#include "cub3d.h"

int	ft_mov_validation(t_data *d, int mov_x, int mov_y)
{
	int	sign_x;
	int	sign_y;
	int	x_offset;
	int	y_offset;

	if (mov_x < d->ply.x)
		sign_x = -1;
	else
		sign_x = 1;
	if (mov_y < d->ply.y)
		sign_y = -1;
	else
		sign_y = 1;
	x_offset = d->ply.x_offset * sign_x;
	y_offset = d->ply.y_offset * sign_y;
	if (d->maps.map[(mov_y + y_offset) / CELL][(mov_x + x_offset) / CELL] != '1')
		return (0);
	return (1);
}
