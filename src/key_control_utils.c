

#include "cub3d.h"

int	ft_mov_validation(t_data *d, int mov_x, int mov_y)
{
	if (d->maps.map[(mov_y - OFFSET) / CELL][(mov_x - OFFSET) / CELL] == '1')
		return (1);
	if (d->maps.map[(mov_y - OFFSET) / CELL][(mov_x + OFFSET) / CELL] == '1')
		return (1);
	if (d->maps.map[(mov_y + OFFSET) / CELL][(mov_x - OFFSET) / CELL] == '1')
		return (1);
	if (d->maps.map[(mov_y + OFFSET) / CELL][(mov_x + OFFSET) / CELL] == '1')
		return (1);
	return (0);
}
