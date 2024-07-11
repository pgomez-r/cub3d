

#include "cub3d.h"

int	ft_load_textures(t_data *d, t_info_map *t)
{
	d->imgs.no_texture = mlx_load_png(t->north_texture_path);
	if (!d->imgs.no_texture)
		return (ft_printf_error("Error loading textures\n"), -1);
	d->imgs.so_texture = mlx_load_png(t->south_texture_path);
	if (!d->imgs.so_texture)
		return (ft_printf_error("Error loading textures\n"), -1);
	d->imgs.ea_texture = mlx_load_png(t->east_texture_path);
	if (!d->imgs.ea_texture)
		return (ft_printf_error("Error loading textures\n"), -1);
	d->imgs.we_texture = mlx_load_png(t->west_texture_path);
	if (!d->imgs.we_texture)
		return (ft_printf_error("Error loading textures\n"), -1);
	return (0);
}

void	ft_set_background(t_data *d)
{
	int	y;
	int	x;

	y = -1;
	while ((unsigned int)++y < d->imgs.game_view->height)
	{
		x = -1;
		while ((unsigned int)++x < d->imgs.game_view->width)
		{
			if ((unsigned int)y < (d->imgs.game_view->height / 2))
				mlx_put_pixel(d->imgs.game_view, x, y, d->imgs.c_color);
			else
				mlx_put_pixel(d->imgs.game_view, x, y, d->imgs.f_color);
		}
	}
}

int	ft_load_images(t_data *d, t_info_map *info_map)
{
	d->exit_code = ft_load_textures(d, info_map);
	if (d->exit_code == 0)
	{
		d->imgs.game_view = mlx_new_image(d->game, WIDTH, HEIGHT);
		ft_set_background(d);
		mlx_image_to_window(d->game, d->imgs.game_view, 0, 0);
		ft_create_minipmap(d);
	}
	return (d->exit_code);
}

