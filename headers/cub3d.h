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
	VOID = -1,
	FLOOR,
	WALL,
}

typedef struct s_mlx_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}			t_mlx_img;

typedef struct s_point
{
	int	x;
	int	y;
}		t_point;

typedef struct s_vector2D
{
	float	x;
	float	y;
}		t_vector2D;

typedef struct s_player
{
	t_vector2D	pos;
	t_vector2D	fwd;
	int			spawn_x;
	int			spawn_y;
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
	t_global	*global;
}			t_datamap;	

typedef struct s_mlx_data
{
	void		*win;
	void		*mlx;
	t_mlx_img	img;
}			t_mlx_data;

typedef struct s_global
{
	int			error;
	t_player	*player;
	t_datamap	*map;
	t_mlx_data	*data;
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

/*	ERROR	*/
int		parsing_error(int code, t_global *global);
int		minimap_error(int code, t_global *global);

/*	MINIMAP	*/
int		minimap(t_mlx_data *data, t_global *global);
int		drawing(t_mlx_data *data, t_global *global);

/*	IMAGE	*/
void	my_pixel_put(t_mlx_img *img, int x, int y, int color);
int		init_image(t_mlx_data *data, t_global *global);

#endif
