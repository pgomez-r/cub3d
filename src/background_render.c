/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:06:56 by pgruz11           #+#    #+#             */
/*   Updated: 2024/08/07 14:26:52 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_render_values(t_data *d, t_render *tx, int y, int x)
{
	if (y == HEIGHT - 1)
	{
		if (x == WIDTH / 2 && d->ply.y != d->flag_y)
		{
			d->flag_y = d->ply.y;
			printf("\nY = %d X = %d\n", y, x);
			printf("PLAYER STATS\n");
			printf("x coord = %f y coord = %f\n", d->ply.x, d->ply.y);
			printf("dir_x = %f dir_y = %f plane_x = %f plane_y = %f \n",
				d->ply.dir_x, d->ply.dir_y, d->ply.plane_x, d->ply.plane_y);
			printf("TEXTURE MAPPING\n");
			printf("step_x = %f step_y = %f\n",
				tx->bg_step_x, tx->bg_step_y);
			printf("bg_x = %f bg_y = %f\n", tx->bg_x, tx->bg_y);
			printf("TEXTURE SCALING\ntex_x = %f, tex_y = %f\n",
				tx->tex_x, tx->tex_y);
			printf("STEP_Y = ROW_DIST [%f] * (dir_y1 [%f] - dir_y0 [%f]) / [1000] == %f\n",
				tx->row_dist, tx->dir_y1, tx->dir_y0, tx->bg_step_y);
		}
	}
}

void	ft_background_render(t_data *d, t_render *tx)
{
	int				y;
	int				x;

	ft_set_dir_and_plane(&d->ply);
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		ft_texture_mapping(tx, y);
		x = 0;
		while (x < WIDTH)
		{
			ft_texture_scaling(d, tx);
			tx->tex_color = ft_get_pix_color(d->imgs.floor_tex,
					(int)tx->tex_x, (int)tx->tex_y);
			mlx_put_pixel(d->imgs.game_view, x, y, tx->tex_color);
			ft_print_render_values(d, tx, y, x);
			x++;
		}
		y++;
	}
}

void	ft_set_dir_and_plane(t_player *player)
{
	double	plane_length;

	plane_length = tan(player->fov / 2) * (WIDTH / HEIGHT);
	player->dir_x = cos(player->ang);
	player->dir_y = sin(player->ang);
	player->plane_x = -player->dir_y * plane_length;
	player->plane_y = player->dir_x * plane_length;
}

void	ft_texture_mapping(t_render *tx, int y)
{
	tx->dir_x0 = tx->dpt->ply.dir_x + tx->dpt->ply.plane_x;
	tx->dir_y0 = tx->dpt->ply.dir_y + tx->dpt->ply.plane_y;
	tx->dir_x1 = tx->dpt->ply.dir_x - tx->dpt->ply.plane_x;
	tx->dir_y1 = tx->dpt->ply.dir_y - tx->dpt->ply.plane_y;
	tx->row_dist = (double)(HEIGHT / 2) / (y - HEIGHT / 2);
	tx->bg_step_x = tx->row_dist * (tx->dir_x1 - tx->dir_x0) / (double)WIDTH;
	tx->bg_step_y = tx->row_dist * (tx->dir_y1 - tx->dir_y0) / (double)WIDTH;
	tx->bg_x = (tx->row_dist * tx->dir_x0);
	tx->bg_y = (tx->row_dist * tx->dir_y0);
}

void	ft_texture_scaling(t_data *d, t_render *tx)
{
	tx->tex_x = (d->imgs.floor_tex->width * (tx->bg_x - floor(tx->bg_x)));
		// % d->imgs.floor_tex->width;
	if (d->tx.tex_x < 0)
		d->tx.tex_x += d->imgs.floor_tex->width;
	else if (d->tx.tex_x >= d->imgs.floor_tex->width)
		d->tx.tex_x -= d->imgs.floor_tex->width;
	tx->tex_y = (d->imgs.floor_tex->height * (tx->bg_y - floor(tx->bg_y)));
		// % d->imgs.floor_tex->height;
	if (d->tx.tex_y < 0)
		d->tx.tex_y += d->imgs.floor_tex->height;
	else if (d->tx.tex_y >= d->imgs.floor_tex->height)
		d->tx.tex_y -= d->imgs.floor_tex->height;
	tx->bg_x += tx->bg_step_x;
	tx->bg_y += tx->bg_step_y;
}
