/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_render.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 20:06:56 by pgruz11           #+#    #+#             */
/*   Updated: 2024/07/28 23:47:12 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
			// tx->tex_x = (int)(tx->bg_x * d->imgs.floor_tex->width)
			// 	% d->imgs.floor_tex->width;
			// tx->tex_y = (int)(tx->bg_y * d->imgs.floor_tex->height)
			// 	% d->imgs.floor_tex->height;
			// tx->bg_x += tx->bg_step_x;
			// tx->bg_y += tx->bg_step_y;
			ft_texture_scaling(d, tx);
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
	double	angle;
	double	fov;

	(void)tx;
	angle = player->ang * (M_PI / 180);
	fov = FOV * (M_PI / 180);
	player->dir_x = cos(angle);
	player->dir_y = -sin(angle);
	player->plane_x = cos(angle + M_PI / 2) * tan(fov / 2);
	player->plane_y = -sin(angle + M_PI / 2) * tan(fov / 2);
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
