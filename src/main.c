/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:12:36 by codespace         #+#    #+#             */
/*   Updated: 2024/06/28 15:23:41 by pgruz11          ###   ########.fr       */
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

void	create_minipmap(t_data *d)
{
	d->imgs.minimap = mlx_new_image(d->game, MINI_W, MINI_H);
	d->rc.map_scale_x = (float)d->imgs.minimap->width / WIDTH;
	d->rc.map_scale_y = (float)d->imgs.minimap->height / HEIGTH;
	paint_map(d, MINI_W, MINI_H);
	mlx_image_to_window(d->game, d->imgs.minimap, 0, 0);
}

void	ft_set_background(mlx_image_t *img)
{
	int y;
	int	x;

	y = -1;
	while ((unsigned int)++y < img->width)
	{
		x = -1;
		while ((unsigned int)++x < img->height)
		{
			if ((unsigned int)y < (img->width / 2))
				mlx_put_pixel(img, x, y, BLUE);
			else
				mlx_put_pixel(img, x, y, GREEN);
		}
	}
}

void	ft_load_images(t_data *d)
{
	d->imgs.game_view = mlx_new_image(d->game, WIDTH, HEIGTH);
	ft_set_background(d->imgs.game_view);
	mlx_image_to_window(d->game, d->imgs.game_view, 0, 0);
	create_minipmap(d);
}

void	game_hook(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (d->exit_code == 0)
	{
		key_control(d);
		update_minimap(d);
	}
}

int	main(void)
{
	t_data	d;

	ft_init(&d);
	if (d.exit_code == 0)
	{
		d.game = mlx_init(WIDTH, HEIGTH, "CVB3D", false);
		ft_load_images(&d);
		place_player(&st);
		//render_map(&st);
		//create_minipmap(&st);
		mlx_loop_hook(st.game, game_hook, &st);
		mlx_loop(st.game);
		mlx_terminate(st.game);
	}
	return (0);
}
