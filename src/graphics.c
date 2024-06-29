/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfxics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 09:09:15 by pgruz11           #+#    #+#             */
/*   Updated: 2024/06/06 15:39:45 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	paint_map(t_mlx_st *st, size_t w, size_t h)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			if (st->d->map[y / (PIX / 4)][x / (PIX / 4)] == '1')
				mlx_put_pixel(st->gfx.minimap, x, y, 0x000000FF);
			else
				mlx_put_pixel(st->gfx.minimap, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
}

void	create_minipmap(t_mlx_st *st)
{
	st->d->mini_w = (st->d->width * PIX) / 4;
	st->d->mini_h = (st->d->height * PIX) / 4;
	st->gfx.minimap = mlx_new_image(st->game, st->d->mini_w, st->d->mini_h);
	paint_map(st, st->d->mini_w, st->d->mini_h);
	mlx_image_to_window(st->game, st->gfx.minimap, 0, 0);
	//mlx_set_instance_depth(&st->gfx.minimap->instances[0], 10);
	st->d->scale_x = (float)st->gfx.minimap->width / (st->d->width * PIX);
	st->d->scale_y = (float)st->gfx.minimap->height / (st->d->height * PIX);
}

void	paint_square(mlx_image_t *square, int size, int color)
{
	int			y;
	int			x;

	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
			mlx_put_pixel(square, x, y, color);
	}
}

