

#include "cub3d.h"

unsigned int	ft_img_color(mlx_image_t *tex, int x, int y)
{
	unsigned int	pos;
	int				r;
	int				g;
	int				b;
	int				a;

	pos = 4 * x + (4 * y * tex->width);
	if (pos <= tex->height * tex->width * 4)
	{
		r = tex->pixels[pos];
		g = tex->pixels[pos + 1];
		b = tex->pixels[pos + 2];
		a = tex->pixels[pos + 3];
		return (r << 24 | g << 16 | b << 8 | a);
	}
	return (0);
}

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

void	ft_set_background(mlx_image_t *img)
{
	int	y;
	int	x;

	y = -1;
	while ((unsigned int)++y < img->height)
	{
		x = -1;
		while ((unsigned int)++x < img->width)
		{
			if ((unsigned int)y < (img->height / 2))
				mlx_put_pixel(img, x, y, BLUE);
			else
				mlx_put_pixel(img, x, y, GREEN);
		}
	}
}

int	ft_load_images(t_data *d, t_info_map *info_map)
{
	d->exit_code = ft_load_textures(d, info_map);
	if (d->exit_code == 0)
	{
		d->imgs.game_view = mlx_new_image(d->game, WIDTH, HEIGHT);
		ft_set_background(d->imgs.game_view);
		mlx_image_to_window(d->game, d->imgs.game_view, 0, 0);
		ft_create_minipmap(d);
	}
	return (d->exit_code);
}
