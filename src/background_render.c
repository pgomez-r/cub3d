/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:06:56 by pgruz11           #+#    #+#             */
/*   Updated: 2024/08/03 12:43:32 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_render_values(t_data *d, t_render *tx, int y, int x)
{
	if (y == HEIGHT - 1 || y == HEIGHT / 2)
	{
		if (x == 0 || x == WIDTH - 1 || x == WIDTH / 2)
		{
			printf("\nY = %d X = %d\n", y, x);
			printf("PLAYER STATS\n");
			printf("x coord = %f y coord = %f\n", d->ply.x, d->ply.y);
			printf("dir_x = %f dir_y = %f plane_x = %f plane_y = %f \n",
				d->ply.dir_x, d->ply.dir_y, d->ply.plane_x, d->ply.plane_y);
			printf("RAYS DIRECTIONS\n");
			printf("dirRX0 = %f dirRX1 = %f dirRY0 = %f dirRY1 = %f\n",
				tx->dir_x0, tx->dir_x1, tx->dir_y0, tx->dir_y1);
			printf("bg_x = %f bg_y = %f\n", tx->bg_x, tx->bg_y);
			printf("TEXTURE SCALING\ntex_x = %f, tex_y = %f\n",
				tx->tex_x, tx->tex_y);
		}
	}
}

void	ft_texture_scaling(t_data *d, t_render *tx)
{
	int	cell_x;
	int	cell_y;

	cell_x = (int)tx->bg_x;
	cell_y = (int)tx->bg_y;
	tx->tex_x = (int)(d->imgs.floor_tex->width * (tx->bg_x - cell_x))
		% d->imgs.floor_tex->width;
	tx->tex_y = (int)(d->imgs.floor_tex->height * (tx->bg_y - cell_y))
		% d->imgs.floor_tex->height;
	tx->bg_x += tx->bg_step_x;
	tx->bg_y += tx->bg_step_y;
}

void	ft_background_render(t_data *d, t_render *tx)
{
	int				y;
	int				x;

	ft_set_dir_and_plane(&d->ply, tx);
	y = HEIGHT / 2;
	while (y < HEIGHT)
	{
		ft_texture_mapping(tx, y);
		x = 0;
		while (x < WIDTH)
		{
			ft_texture_scaling(d, tx);
			ft_print_render_values(d, tx, y, x);
			tx->tex_color = ft_get_pix_color(d->imgs.floor_tex,
					tx->tex_x, tx->tex_y);
			mlx_put_pixel(d->imgs.game_view, x, y, tx->tex_color);
			x++;
		}
		y++;
	}
}

void	ft_set_dir_and_plane(t_player *player, t_render *tx)
{
	double	fov_rad;
	double	plane_length;

	fov_rad = FOV * M_PI / 180.0;
	plane_length = tan(fov_rad / 2);
	(void)tx;
	if (cos(player->ang) > 0)
		player->dir_x = 1;
	else
		player->dir_x = -1;
	if (sin(player->ang) > 0)
		player->dir_y = -1;
	else
		player->dir_y = 1;
	player->plane_x = -player->dir_y * plane_length;
	player->plane_y = player->dir_x * plane_length;
}

void	ft_texture_mapping(t_render *tx, int y)
{
	tx->dir_x0 = tx->dpt->ply.dir_x - tx->dpt->ply.plane_x;
	tx->dir_x1 = tx->dpt->ply.dir_x + tx->dpt->ply.plane_x;
	tx->dir_y0 = tx->dpt->ply.dir_y - tx->dpt->ply.plane_y;
	tx->dir_y1 = tx->dpt->ply.dir_y + tx->dpt->ply.plane_y;
	tx->row_dist = (0.5 * HEIGHT) / (y - HEIGHT / 2);
	tx->bg_step_x = tx->row_dist * (tx->dir_x1 - tx->dir_x0) / WIDTH;
	tx->bg_step_y = tx->row_dist * (tx->dir_y1 - tx->dir_y0) / WIDTH;
	tx->bg_x = tx->dpt->ply.x + tx->row_dist * tx->dir_x0;
	tx->bg_y = tx->dpt->ply.y + tx->row_dist * tx->dir_y0;
}
