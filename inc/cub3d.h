/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgruz11 <pgruz11@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 00:13:53 by codespace         #+#    #+#             */
/*   Updated: 2024/06/29 23:07:52 by pgruz11          ###   ########.fr       */
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
# define N_RAYS 120 //Number of rays to cast - has to be proportional to FOV value!
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
typedef struct s_map		t_map; 	//main map and mimimap info and value
typedef struct s_visual		t_visual; //mlx textures, images and other visuals
typedef struct s_player		t_player; //first person view player info and values
typedef struct s_rays		t_rays; //raycasting variables and values
typedef struct s_data		t_data; //general program data

typedef struct s_data
{
	t_map		maps;
	t_visual	imgs;
	t_player	ply;
	t_rays		rc;
	mlx_t		*game;
	int			exit_code;
}	t_data;

typedef struct s_map
{
	t_data		*dpt;
	char		**map;
	int			map_width;
	int			map_height;
	int			pix_width;
	int			pix_height;
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
	mlx_image_t	*minimap;
}	t_visual;

typedef struct s_rays
{
	t_data	*dpt;
	float	curr_ang;
	float	incr_ang;
	double 	ray_x;
	double	ray_y;
	float	map_scale_x;
	float	map_scale_y;
	float	wall_dist;
	float	wall_height;
}	t_rays;

/*--------_SRC_FUNCTIONS_--------*/
/*init.c*/
void			ft_init(t_data *d);
void			ft_fake_map_parse(t_data *d);
void			ft_map_maker(t_data *d);
void			ft_place_player(t_data *d);
/*load_images.c*/
void			ft_load_images(t_data *d);
void			ft_set_background(mlx_image_t *img);
void			ft_create_minipmap(t_data *d);
void			ft_paint_map(t_data *d, size_t w, size_t h);

# endif
