
#ifndef CUB3D_H
# define CUB3D_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include "minilibx-linux/mlx_int.h"
# include "get_next_line/get_next_line.h"
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

# define WIDTH	1920
# define HEIGHT	1080

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
	WRONGTEXTURE
}	t_error;

typedef struct s_global
{
	int	error;
}		t_global;

typedef struct s_vector2D
{
	float	x;
	float	y;
}		t_vector2D;

typedef struct s_player
{
	t_vector2D	pos;
	t_vector2D	fwd;
}		t_player;

typedef struct s_datamap
{
	int			**map;
	int			width;
	int			height;
	char		*north_t;
	char		*south_t;
	char		*east_t;
	char		*west_t;
	int			floor;
	int			ceiling;
	t_global	*global;
}			t_datamap;	

typedef struct s_mlx_data
{
	void	*win;
	void	*mlx;
}			t_mlx_data;

/*	PARSING	*/
int		parsing(char **argv, int argc, t_datamap *map);
int		parsing_error(int code, t_global *global);
int		iscolor(char *str, t_datamap *map);
int		istexture(char *str, t_datamap *map);
void	clear_gnl(char *str, int fd);
void	clear_textures(t_datamap *map);

#endif
