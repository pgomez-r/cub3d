/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfredes- <gfredes-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:12:36 by codespace         #+#    #+#             */
/*   Updated: 2024/07/03 19:16:25 by gfredes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_paint_miniplayer(t_data *d)
{
	float	player_x;
	float	player_y;
	int		i;
	int		j;

	player_x = d->ply.x * d->maps.map_scale_x;
	player_y = d->ply.y * d->maps.map_scale_y;
	i = -1;
	while (i < 2)
	{
		j = -1;
		while (j < 2)
		{
			mlx_put_pixel(d->imgs.mini_src, (int)player_x + j,
				(int)player_y + i, RED);
			j++;
		}
		i++;
	}
}

void	ft_game_hook(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (d->exit_code == 0)
	{
		ft_key_control(d);
		ft_paint_minimap(d, d->maps.minimap_w, d->maps.minimap_h);
		ft_paint_miniplayer(d);
		ft_raycast(d, &d->rc, d->maps.map_scale_x, d->maps.map_scale_y);
	}
}

void	print_map_info(t_info_map *info_map)
{
	int	y;

	y = 0;
	printf("North texture: %s\n", info_map->north_texture_path);
	printf("South texture: %s\n", info_map->south_texture_path);
	printf("East texture: %s\n", info_map->east_texture_path);
	printf("West texture: %s\n", info_map->west_texture_path);
	printf("Floor: %d, %d, %d\n", info_map->floor[0], info_map->floor[1], info_map->floor[2]);
	printf("Ceiling: %d, %d, %d\n", info_map->ceiling[0], info_map->ceiling[1], info_map->ceiling[2]);
	printf("Map_width: %d\n", info_map->map_width);
	printf("Map_heigth: %d\n", info_map->map_height);
	printf("Map_status: %d\n", info_map->map_status);
	printf("Player_view: %c\n", info_map->player_view);
	printf("Map:\n");
	while (info_map->map[y])
	{
		//printf("len line %d: %ld\n", y, ft_strlen(info_map->map[y]));
		printf("%s\n", info_map->map[y]);
		y++;
	}
	printf("\n");
}

int	main(int argc, char **argv)
{
	t_data		d;
	t_info_map	info_map;

	ft_init(&d);
	check_args(argc, argv);
	info_map = init_map();
	get_map_info(argv[1], &info_map);
	print_map_info(&info_map);
	if (d.exit_code == 0)
	{
		d.game = mlx_init(WIDTH, HEIGTH, "CVB3D", false);
		ft_load_images(&d);
		mlx_loop_hook(d.game, ft_game_hook, &d);
		mlx_loop(d.game);
		mlx_terminate(d.game);
	}
	free_map(&info_map);
	return (0);
}
