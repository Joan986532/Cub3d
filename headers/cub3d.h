#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include "mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "mlx_int.h"
# include "get_next_line.h"
# include <math.h>

# define S_LIMITCOLOR "Color limit is 255\n"
# define S_WRONGCOLOR "Color is uninitialized\n"
# define S_NOWHITESPACE "Need at least one white space\n"
# define S_SYNTAX "Syntax error in map\n"
# define S_EXTENSION "Need .cub extension\n"
# define S_OPEN "Map open failed\n"
# define S_WRONGARGS "Need map argument\n"
# define S_ACCESS "Can't access texture\n"
# define S_MALLOC "malloc fail\n"
# define S_WRONGTEXTURE "Texture is uninitialized\n"
# define S_IMAGE "mlx new image fail\n"

# define WIDTH	1920
# define HEIGHT	1080

typedef struct s_global	t_global;

typedef enum s_error
{
	LIMITCOLOR,
	WRONGCOLOR,
	NOWHITESPACE,
	SYNTAX,
	EXTENSION,
	OPEN,
	WRONGARGS,
	ACCESS,
	MALLOC,
	WRONGTEXTURE,
	IMAGE
}	t_error;

typedef enum e_tile
{
	VOID = ' ',
	FLOOR = '0',
	WALL = '1',
}	t_tile;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}		t_texture;

typedef struct s_stripe
{
	int	x;
	int	y0;
	int	y1;
	int	color;
	int	tex_x;
	double	wall_x;
	int	side;
	t_texture	*texture;
	double	perpWallDist;
}		t_stripe;

typedef struct s_mlx_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		error;
}			t_mlx_img;

typedef struct s_point
{
	int	x1;
	int	y1;
	int	x2;
	int	y2;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	error;
	int	error2;
}		t_point;

typedef struct s_vector2D
{
	float	x;
	float	y;
}		t_vector2D;

typedef struct s_vector3D
{
	float	x;
	float	y;
	float	z;
}		t_vector3D;

typedef struct s_rat
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	int	mapX;
	int	mapY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int	stepX;
	int	stepY;
	int	hit;
	int	side;
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	int	color;
	double	wall_x;
	int	tex_x;
	t_texture	*texture;
}		t_rat;

typedef struct s_player
{
	t_vector3D	pos;
	t_vector3D	fwd;
	t_vector3D	spawn;
	t_vector3D	spawn_fwd;
	t_vector3D	plane;
	int			max_render_distance;
	int			minimap_width;
	int			minimap_height;
	float		angle;
	int			forwd;
	int			bckwd;
	int			left;
	int			right;
	int			trnleft;
	int			trnright;
}		t_player;

typedef struct s_datamap
{
	char		**map;
	int			map_height;
	int			map_width;
	char		*north_t;
	char		*south_t;
	char		*east_t;
	char		*west_t;
	int			floor;
	int			ceiling;
	int			size;
	int			error;
	t_player	*player;
}			t_datamap;	

typedef struct s_mlx_data
{
	void		*win;
	void		*mlx;
	t_mlx_img	view;
}			t_mlx_data;

typedef struct s_global
{
	int			error;
	int			press;
	t_player	*player;
	t_datamap	*map;
	t_mlx_data	*data;
	t_texture	*north_texture;
	t_texture	*south_texture;
	t_texture	*east_texture;
	t_texture	*west_texture;
}		t_global;

/*	PARSING	*/
int		parsing(char **argv, int argc, t_datamap *map);
int		iscolor(char *str, t_datamap *map);
int		istexture(char *str, t_datamap *map);
void	clear_gnl(char *str, int fd);
void	clear_textures(t_datamap *map);
void	ft_strtrime(char *str);
int		parse_map(char *str, t_datamap *map, int fd);
void	free_arr(char **arr);
int		is_valid_map(char **map);
int		is_spawn(char c);
int		parsing_extension(char *str, t_datamap *map);
int		verify_struct(t_datamap *map);

/*	RENDER	*/
int		render_frame(void *info);

/*	DRAWING	*/
int		draw_minimap(t_global *global);
int		draw_view(t_mlx_data *data, t_global *global);
int		draw_overlay(t_mlx_data *data, t_global *global);
int		draw_sprite(t_mlx_data *data, t_global *global);



/*	RAYCAST	*/
void	init_ray(t_rat *ray, int x, t_global *global);
void	calculate_step(t_rat *ray, t_player *player);
void	calculate_wall_height(t_rat *ray);
void	set_wall_color(t_rat *ray, t_global *global);
void	perform_dda(t_rat *ray, t_global *global);

/*	STRIPE	*/
void	calculate_texture_params(t_stripe *stripe, double *tex_pos, double *step);
int		get_shaded_color(int color, int side);
void	set_ceiling_floor_colors(t_global *global, int *ceiling, int *floor);
void	set_stripe(t_stripe *stripe, t_rat *ray, int x);

/*	ERROR	*/
int		parsing_error(int code, t_datamap *map);
int		img_error(int code, t_mlx_img *img);

/*	MINIMAP	*/
int		minimap(t_mlx_data *data, t_global *global);
int		drawing(t_global *global);

/*	IMAGE	*/
void	my_pixel_put(t_mlx_img *img, int x, int y, int color);
int		init_image(t_mlx_img *img, void *mlx);
void	bresenham(t_point *point, t_mlx_img *img);

/*	TEXTURE	*/
int		load_textures(t_global *global);
void	free_textures(t_global *global);
int		get_texture_color(t_texture *texture, int x, int y);

/*	CONTROLS	*/
int		key_press(int keysym, t_global *global);
int		key_release(int keysym, t_global *global);
int		mouse_moove(int x, int y, t_global *global);
void	rotate_antitrigo(t_player *player, float angle);
void	rotate_trigo(t_player *player, float angle);
int		close_window(void *data);

/*	PLAYER	*/
void	pov_player(t_mlx_data *data, t_player *player);

#endif
