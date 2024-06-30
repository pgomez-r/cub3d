/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 00:58:21 by pgruz11           #+#    #+#             */
/*   Updated: 2024/06/30 22:11:19 by pgruz11          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_raycast(t_data *d, t_rays *rc)
{
	int		i;
	int		mini_x;
	int		mini_y;

	rc->incr_ang = FOV / (N_RAYS - 1);
	rc->curr_ang = d->ply.ang - (FOV / 2);
	i = -1;
	while (++i < N_RAYS)
	{
		rc->ray_x = d->ply.x;
		rc->ray_y = d->ply.y;
		mini_x = (int)(rc->ray_x * d->maps.map_scale_x);
		mini_y = (int)(rc->ray_y * d->maps.map_scale_y);
		while (d->maps.map[(int)rc->ray_y / CELL][(int)rc->ray_x / CELL] != '1')
		{
			mlx_put_pixel(d->imgs.mini_src, mini_x, mini_y, GREEN);
			rc->ray_y -= sin(rc->curr_ang);
			rc->ray_x += cos(rc->curr_ang);
		}
		ft_wall_render(d, rc, i);
		rc->curr_ang += rc->incr_ang;
	}
}

void	ft_wall_render(t_data *d, t_rays *rc, int ray_num)
{
	int	win_x;
	int	col_width;

	col_width = d->imgs.game_view->width / N_RAYS;
	win_x = ray_num * col_width;
	rc->wall_dist = ft_wall_distance(d, rc);
	rc->wall_height = ft_wall_heigth(rc->wall_dist, PP);
	ft_draw_wall(d, rc, win_x, col_width);
}

void ft_draw_wall(t_data *d, t_rays *rc, int win_x, int col_width)
{
	int	start;
	int	end;
	int	i;
	int	mid_win;
	int	x;

	mid_win = d->imgs.game_view->height / 2;
	start = mid_win - (int)(rc->wall_height / 2);
	if (start < 0) 
		start = 0;
	end = start + (int)rc->wall_height;
	if (end >= (int)d->imgs.game_view->height)
		end = d->imgs.game_view->height - 1;
	x = win_x;
	while (x < (win_x + col_width))
	{
		i = start;
		while (i < end)
		{
			mlx_put_pixel(d->imgs.game_view, x, i, WHITE);
			i++;
		}
		x++;
	}
}

float	ft_wall_distance(t_data *d, t_rays *rc)
{
	return (sqrt(pow(rc->ray_x - d->ply.x, 2)
		+ pow(rc->ray_y - d->ply.y, 2)));
}

int	ft_wall_heigth(float distance, float plane)
{
	float	wall_gh;
	float	height;

	wall_gh = 64.0;
	height = (wall_gh * plane) / distance;
	if (height < 1.0)
		height = 1.0;
	return ((int)height);
}
