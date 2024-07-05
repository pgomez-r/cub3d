

#include "cub3d.h"

void	ft_texture_select(t_data *d)
{
	if (d->rc.wall_dir == 1)
	{
		if (d->rc.dir_y == 1)
			d->tx.tex_ptr = d->imgs.so_texture;
		else
			d->tx.tex_ptr = d->imgs.no_texture;
	}
	else
	{
		if (d->rc.dir_x == 1)
			d->tx.tex_ptr = d->imgs.ea_texture;
		else
			d->tx.tex_ptr = d->imgs.we_texture;
	}
}

void	ft_wall_tex_init(t_data *d, t_rays *rc, int start)
{
	double		wall_x;

	ft_texture_select(d);
	if (rc->wall_dir == 0)
		wall_x = fmod(rc->ray_y, 1.0);
	else
		wall_x = fmod(rc->ray_x, 1.0);
	if (wall_x < 0)
		wall_x += 1.0;
	d->tx.tex_x = (int)(wall_x * (double)(d->tx.tex_ptr->width));
	if ((rc->wall_dir == 0 && rc->ray_x > 0)
		|| (rc->wall_dir == 1 && rc->ray_y < 0))
		d->tx.tex_x = d->tx.tex_ptr->width - d->tx.tex_x - 1;
	d->tx.tex_step = 1.0 * d->tx.tex_ptr->height / d->rc.wall_height;
	d->tx.tex_pos = (start - d->tx.mid_win + (d->rc.wall_height / 2))
		* d->tx.tex_step;
	d->tx.tex_step = 1.0 * d->tx.tex_ptr->height / d->rc.wall_height;
}

void	ft_wall_paint(t_data *d, t_render *tx, int x, int y)
{
	tx->tex_y = (int)tx->tex_pos & (tx->tex_ptr->height - 1);
	tx->tex_color = ft_get_pix_color(tx->tex_ptr, tx->tex_x, tx->tex_y);
	tx->tex_pos += tx->tex_step;
	mlx_put_pixel(d->imgs.game_view, x, y, tx->tex_color);
}

unsigned int	ft_get_pix_color(mlx_texture_t *tex, int x, int y)
{
	unsigned int	pos;
	int				r;
	int				g;
	int				b;
	int				a;

	pos = 4 * x + (4 * y * tex->width);
	if (pos <= tex->height * tex->width * tex->bytes_per_pixel)
	{
		r = tex->pixels[pos];
		g = tex->pixels[pos + 1];
		b = tex->pixels[pos + 2];
		a = tex->pixels[pos + 3];
		return (r << 24 | g << 16 | b << 8 | a);
	}
	return (0);
}
