
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

# define S_LIMITCOLOR "color limit is 255\n"
# define S_NOWHITESPACE "need at least one white space\n"
# define S_SYNTAX "maximum two caps letter for identifier\n"
# define S_EXTENSION "map extension is .cub\n"
# define S_OPEN "map open failed\n"
# define S_WRONGARGS "need arg map.cub\n"

# define WIDTH	1920
# define HEIGHT	1080

typedef enum s_error
{
	LIMITCOLOR,
	NOWHITESPACE,
	SYNTAX,
	EXTENSION,
	OPEN,
	WRONGARGS
}	t_error;

typedef struct s_global
{
	int	error;
}		t_global;

typedef struct s_datamap
{
	char		*north_t;
	char		*south_t;
	char		*east_t;
	char		*west_t;
	char		*floor_c;
	char		*ceiling_c;
	char		*sky_c;
	t_global	*global;
}			t_datamap;	

typedef struct s_mlx_data
{
	void	*win;
	void	*mlx;
}			t_mlx_data;

int	map_parsing(char **argv, int argc);
int	parsing_error(int code, t_global *global);

#endif
