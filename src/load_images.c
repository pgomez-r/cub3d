
#include "cub3d.h"

void	ft_paint_map(t_data *d, size_t w, size_t h)
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

void	ft_create_minipmap(t_data *d)
{
	d->imgs.minimap = mlx_new_image(d->game, MINI_W, MINI_H);
	d->rc.map_scale_x = (float)d->imgs.minimap->width / WIDTH;
	d->rc.map_scale_y = (float)d->imgs.minimap->height / HEIGTH;
	ft_paint_map(d, MINI_W, MINI_H);
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
	ft_create_minipmap(d);
}

