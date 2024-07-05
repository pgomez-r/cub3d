

#include "cub3d.h"

/*This function bellow is in working progress, still needs many tests*/
void	ft_wall_render(t_data *d, t_rays *rc, int ray_num)
{
	double	win_x;
	double	col_width;
	int		end_x;

	col_width = (double)WIDTH / N_RAYS;
	if (ray_num == 0)
		win_x = 0;
	else
		win_x = round(ray_num * col_width);
	if (ray_num == N_RAYS - 1)
		end_x = WIDTH;
	else
		end_x = round((ray_num + 1) * col_width) - 1;
	rc->wall_dist = ft_wall_distance(d, rc);
	rc->wall_height = ft_wall_heigth(rc->wall_dist, PP);
	ft_draw_wall(d, rc, win_x, (end_x - win_x) + 1);
}

void ft_draw_wall(t_data *d, t_rays *rc, int win_x, int col_width)
{
	int	start;
	int	end;
	int	y;
	int	x;

	d->tx.mid_win = HEIGTH / 2;
	start = d->tx.mid_win - (int)(rc->wall_height / 2);
	if (start < 0) 
		start = 0;
	end = start + (int)rc->wall_height;
	if (end >= HEIGTH)
		end = HEIGTH - 1;
	ft_wall_tex_init(d, rc, start);
	x = win_x;
	while (x < (win_x + col_width))
	{
		y = start;
		while (y < end)
		{
			ft_wall_paint(d, &d->tx, x, y);
			y++;
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

	wall_gh = (float)CELL;
	height = (wall_gh * plane) / distance;
	if (height < 1.0)
		height = 1.0;
	return ((int)height);
}
