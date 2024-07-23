
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
# define WIDTH 1000
# define HEIGHT 800
# define ASPECT_RATIO ((float)WIDTH / (float)HEIGHT)
# define MINI_W (WIDTH / 4)
# define MINI_H (HEIGHT / 4)
# define CELL 64
# define MINICELL (CELL / 4)
# define MOV 4
# define OFFSET 8
# define FOV (60 * (M_PI / 180))
# define N_RAYS (WIDTH)
# define PP ((WIDTH / 2) / tan(FOV / 2))
# define NORTH (M_PI / 2)
# define EAST (2 * M_PI)
# define SOUTH ((3 * M_PI) / 2)
# define WEST M_PI

/*Colors*/
# define BLACK 0x000000FF
# define WHITE 0xFFFFFFFF
# define BLUE 0xADD8E6
# define PINK 0xFFC0CBFF
# define RED 0xFF0000FF
# define GREEN 0x007F007F
# define TRANSP 0xFF000000
# define GREY 0xA9A9A9FF

/*Structs declaration*/
typedef struct s_data		t_data;
typedef struct s_map		t_map;
typedef struct s_visual		t_visual;
typedef struct s_player		t_player;
typedef struct s_rays		t_rays;
typedef struct s_render		t_render;

/*Structs definition*/
typedef struct s_info_map
{
	char			*north_texture_path;
	char			*south_texture_path;
	char			*east_texture_path;
	char			*west_texture_path;
	int				floor[3];
	int				ceiling[3];
	unsigned int	floor_hex;
	unsigned int	ceiling_hex;
	int				map_width;
	int				map_height;
	int				map_status;
	int				player;
	char			player_view;
	char			**map;
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

typedef struct s_render
{
	t_data			*dpt;
	int				mid_win;
	double			tex_x;
	double			tex_y;
	float			tex_step;
	unsigned int	tex_color;
	mlx_texture_t	*tex_ptr;
}	t_render;

typedef struct s_visual
{
	t_data			*dpt;
	unsigned int	f_color;
	unsigned int	c_color;
	mlx_image_t		*game_view;
	mlx_image_t		*mini_src;
	mlx_image_t		*mini_view;
	mlx_texture_t	*no_texture;
	mlx_texture_t	*so_texture;
	mlx_texture_t	*ea_texture;
	mlx_texture_t	*we_texture;
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
	float	init_x;
	float	init_y;
	float	delta_x;
	float	delta_y;
	int		dir_x;
	int		dir_y;
	int		wall_dir;
	double	wall_hp;
}	t_rays;

typedef struct s_data
{
	t_map		maps;
	t_visual	imgs;
	t_player	ply;
	t_rays		rc;
	t_render	tx;
	mlx_t		*game;
	int			exit_code;
}	t_data;

/*--------_SRC_FUNCTIONS_--------*/
/***************main.c***************/
void			ft_game_hook(void *param);
/***************init.c***************/
void			ft_set_player_view(char view, t_data *d);
void			ft_init(t_data *d);
void			ft_map_parse(t_data *d, t_info_map *info_map);
void			ft_place_player(t_data *d);
t_info_map		ft_init_map(void);
/***************load_images.c***************/
int				ft_load_images(t_data *d, t_info_map *info_map);
void			ft_set_background(t_data *d);
int				ft_load_textures(t_data *d, t_info_map *t);
unsigned int	ft_img_color(mlx_image_t *tex, int x, int y);
/***************minimap.c***************/
void			ft_create_minipmap(t_data *d);
void			ft_paint_minimap(t_data *d, size_t w, size_t h);
void			ft_paint_miniplayer(t_data *d);
void			ft_paint_miniview(t_data *d);
int				ft_minimap_limits(int x, int y, mlx_image_t *img);
/***************key_control.c***************/
void			ft_move_right(t_data *d);
void			ft_move_left(t_data *d);
void			ft_move_down(t_data *d);
void			ft_move_up(t_data *d);
void			ft_key_control(t_data *d);
/***************key_control_utils.c***************/
int				ft_mov_validation(t_data *d, int x, int y);
float			ft_normalize_angle(float angle);
/***************raycast.c***************/
void			ft_raycast(t_data *d, t_rays *rc, float scale_x, float scale_y);
void			ft_init_ray_step(t_data *d, t_rays *rc);
void			ft_init_delta_step(t_rays *rc);
int				ft_push_ray(t_rays *rc);
/***************wall_render.c***************/
void			ft_wall_render(t_data *d, t_rays *rc, int ray_num);
void			ft_draw_wall(t_data *d, t_rays *rc, int ray_num);
void			ft_wall_tex_init(t_data *d, t_rays *rc);
void			ft_wall_paint(t_data *d, t_render *tx, int x, int i);
/***************wall_render_utils.c***************/
float			ft_wall_distance(t_data *d, t_rays *rc);
int				ft_wall_height(float distance, float plane);
void			ft_texture_select(t_data *d);
unsigned int	ft_get_pix_color(mlx_texture_t *tex, int x, int y);
void			ft_wall_hitpoint(t_rays *rc);
/***************check_args.c***************/
static int		ft_check_file_name(char *argv);
void			ft_check_args(int argc, char **argv);
void			ft_check_rgb_color(char *color);
void			ft_invalid_map(int mode);
/***************check_map.c***************/
int				ft_check_line_map(char *line, int mode);
void			ft_check_all_ones(char *line);
int				ft_check_valid_neighbor(t_info_map *info_map, int y, int x);
void			ft_check_map_limits(t_info_map *info_map, int y);
void			ft_check_closed_map(t_info_map *info_map);
/***************colors_and_textures.c***************/
void			ft_get_texture(char **texture, t_info_map *info_map);
void			ft_get_color(char **texture, t_info_map *info_map);
void			ft_remove_nl(char **texture);
void			ft_get_textures_and_colors(char *line, t_info_map *info_map, int *n);
void			ft_rgb_to_hex(t_info_map *info_map);
/***************free.c***************/
void			ft_free_split(char **split);
void			ft_free_map(t_info_map *info_map);
/***************map_size.c***************/
void			ft_get_width(char *line, t_info_map *info_map);
void			ft_get_map_size(int fd, t_info_map *info_map);
/***************map.c***************/
void			ft_check_valid_color(t_info_map *info_map);
static void		ft_get_line_map(char *line, t_info_map *info_map, int y);
static void		ft_get_map(char *line, t_info_map *info_map, int *n);
static void		ft_get_line_info(char *line, int fd, t_info_map *info_map, int *n);
void			ft_get_map_info(char *file, t_info_map *info_map);

#endif
