

#include "cub3d.h"

/*This function bellow is in working progress, still needs many tests*/
void	ft_wall_render(t_data *d, t_rays *rc, int ray_num)
{
	rc->wall_dist = ft_wall_distance(d, rc);
	rc->wall_height = ft_wall_heigth(rc->wall_dist, PP);
	ft_draw_wall(d, rc, ray_num);
}

void ft_draw_wall(t_data *d, t_rays *rc, int ray_num)
{
	int	start;
	int	end;
	int	y;

	d->tx.mid_win = HEIGTH / 2;
	start = d->tx.mid_win - (int)(rc->wall_height / 2);
	if (start < 0) 
		start = 0;
	end = start + (int)rc->wall_height;
	if (end >= HEIGTH)
		end = HEIGTH - 1;
	ft_wall_tex_init(d, rc, start);
	y = start;
	while (y < end)
	{
		ft_wall_paint(d, &d->tx, ray_num, y);
		y++;
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
}

void	ft_wall_paint(t_data *d, t_render *tx, int x, int y)
{
	tx->tex_y = (int)tx->tex_pos & (tx->tex_ptr->height - 1);
	tx->tex_color = ft_get_pix_color(tx->tex_ptr, tx->tex_x, tx->tex_y);
	tx->tex_pos += tx->tex_step;
	mlx_put_pixel(d->imgs.game_view, x, y, tx->tex_color);
}
