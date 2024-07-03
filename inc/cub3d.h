/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfredes- <gfredes-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:13:53 by codespace         #+#    #+#             */
/*   Updated: 2024/07/03 21:57:23 by gfredes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/*Buffer size for GNL*/
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# include "libft/inc/libft.h"
# include "MLX42/include/MLX42/MLX42.h"
# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>

/*PRE-DEFINED VALUES FOR THE GAME*/
# define NAME "CVB3D"
# define WIDTH 800 //Screen width in pixels
# define HEIGTH 600 //Screen height in pixels
# define MINI_W (WIDTH / 4) //Minimap width in pixels
# define MINI_H (HEIGTH / 4) //Minimap height in pixels
# define CELL 64 //Pixel size of each "cell" of the map - maybe we won't need to use it
# define MINICELL (CELL / 4) //Pixel size of each "cell" of the minimap - maybe we won't need to use it
# define MOV 4 //Number of pixels to move per step - will affect game speed
# define FOV (60 * (M_PI / 180)) //Player's FieldOfView in gradiants -degrees * (M_PI / 180)-
# define N_RAYS (WIDTH) //Number of rays to cast - has to be proportional to FOV value!
# define PP ((WIDTH / 2) / tan(FOV / 2))//Projection plane
# define NORTH (M_PI / 2)
# define EAST (2 * M_PI)
# define SOUTH M_PI
# define WEST ((3 * M_PI) / 2)

/*Colors*/
# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF
# define BLUE 0xADD8E6
# define PINK 0xFFC0CBFF
# define RED 0xFF0000FF
# define GREEN 0x007F007F
# define TRANSP 0xFF000000

/*Structs declaration*/
typedef struct s_data		t_data; //general program data
typedef struct s_map		t_map; //main map and mimimap info and value
typedef struct s_visual		t_visual; //mlx textures, images and other visuals
typedef struct s_player		t_player; //first person view player info and values
typedef struct s_rays		t_rays; //raycasting variables and values

/*Structs definition*/

typedef struct s_info_map
{
	char	*north_texture_path;
	char	*south_texture_path;
	char	*east_texture_path;
	char	*west_texture_path;
	int		floor[3];
	int		ceiling[3];
	int		map_width;
	int		map_height;
	int		map_status;
	int		player;
	char	player_view;
	char	**map;
}	t_info_map;

typedef struct s_map
{
	t_data		*dpt;
	char		**map;
	int			map_width;
	int			map_height;
	int			pix_width;
	int			pix_height;
	int			minimap_w;
	int			minimap_h;
	float		map_scale_x;
	float		map_scale_y;
}	t_map;

typedef struct s_player
{
	t_data		*dpt;
	double		x;
	double		y;
	double		ang;	
}	t_player;

typedef struct s_visual
{
	t_data		*dpt;
	int			f_color;
	int			c_color;
	mlx_image_t	*game_view;
	mlx_image_t	*mini_src;
	mlx_image_t	*mini_view;
}	t_visual;

typedef struct s_rays
{
	t_data	*dpt;
	float	curr_ang;
	float	incr_ang;
	double	ray_x;
	double	ray_y;
	float	wall_dist;
	float	wall_height;
}	t_rays;

typedef struct s_data
{
	t_map		maps;
	t_visual	imgs;
	t_player	ply;
	t_rays		rc;
	mlx_t		*game;
	int			exit_code;
}	t_data;

/*--------_SRC_FUNCTIONS_--------*/
/*init.c*/
void		ft_init(t_data *d);
void		ft_map_parse(t_data *d, t_info_map *info_map);
void		ft_map_maker(t_data *d);
void		ft_place_player(t_data *d);
t_info_map	ft_init_map(void);
/*load_images.c*/
void		ft_load_images(t_data *d);
void		ft_set_background(mlx_image_t *img);
void		ft_create_minipmap(t_data *d);
void		ft_paint_minimap(t_data *d, size_t w, size_t h);
/*key_control.c*/
void		ft_move_right(t_data *d);
void		ft_move_left(t_data *d);
void		ft_move_down(t_data *d);
void		ft_move_up(t_data *d);
void		ft_key_control(t_data *d);
/*raycast.c*/
void		ft_raycast(t_data *d, t_rays *rc, float scale_x, float scale_y);
void		ft_wall_render(t_data *d, t_rays *rc, int ray_num);
void		ft_draw_wall(t_data *d, t_rays *rc, int win_x, int col_width);
float		ft_wall_distance(t_data *d, t_rays *rc);
int			ft_wall_heigth(float distance, float plane);
/*main.c*/
void		ft_game_hook(void *param);
void		ft_paint_miniplayer(t_data *d);
// check_args.c
void		ft_check_args(int argc, char **argv);
// check_map.c
int			ft_check_line_map(char *line, int mode);
void		ft_check_all_ones(char *line);
int			ft_check_valid_neighbor(t_info_map *info_map, int y, int x);
void		ft_check_map_limits(t_info_map *info_map, int y);
void		ft_check_closed_map(t_info_map *info_map);
// colors_and_textures.c
void		ft_get_texture(char **texture, t_info_map *info_map);
void		ft_get_color(char **texture, t_info_map *info_map);
void		ft_get_textures_and_colors(char *line, t_info_map *info_map, int *n);
//error.c
void		ft_invalid_map(int mode);
// free.c
void		ft_free_split(char **split);
void		ft_free_map(t_info_map *info_map);
// map_size.c
void		ft_get_width(char *line, t_info_map *info_map);
void		ft_get_map_size(int fd, t_info_map *info_map);
// map.c
void		ft_get_map_info(char *file, t_info_map *info_map);

#endif
