/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 01:15:37 by pgruz11           #+#    #+#             */
/*   Updated: 2024/06/28 15:02:08 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	paint_miniplayer(mlx_image_t *mini, size_t *x, size_t *y)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			mlx_put_pixel(mini, *x + j, *y + i, 0xFF0000FF);
			j++;
		}
		i++;
	}
	*(x) += 4;
	//*(y) += 4;
	return (4);
}

void	update_minimap(t_mlx_st *st)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < st->d->mini_h)
	{
		x = 0;
		while (x < st->d->mini_w)
		{
			if (st->d->map[y / (PIX / 4)][x / (PIX / 4)] == '1')
				mlx_put_pixel(st->gfx.minimap, x, y, 0x000000FF);
			else
				mlx_put_pixel(st->gfx.minimap, x, y, 0xFFFFFFFF);
			x++;
		}
		y++;
	}
	x = st->gfx.player->instances[0].x / 4;
	y = st->gfx.player->instances[0].y / 4;
	paint_miniplayer(st->gfx.minimap, &x, &y);
	//basic_ray(st);
	cast_rays_range(st, &st->rc);
}

void	place_player(t_mlx_st *st)
{
	int	y;
	int	x;

	y = -1;
	while (++y < (int)st->d->height)
	{
		x = -1;
		while (++x < (int)st->d->width)
		{
			if (st->d->map[y][x] == 'P')
			{
				mlx_image_to_window(st->game, st->gfx.player, (x * PIX) + 24, (y * PIX) + 24);
				//mlx_set_instance_depth(&st->gfx.player->instances[0], 10);
				st->gfx.player->enabled = false;
			}
		}
	}
}
