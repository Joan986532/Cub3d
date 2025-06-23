#include "cub3d_bonus.h"

int	parsing_error(int code, t_datamap *map)
{
	map->error = -1;
	if (code == LIMITCOLOR)
		ft_putstr_fd(S_LIMITCOLOR, 2);
	if (code == WRONGCOLOR)
		ft_putstr_fd(S_WRONGCOLOR, 2);
	if (code == NOWHITESPACE)
		ft_putstr_fd(S_NOWHITESPACE, 2);
	if (code == SYNTAX)
		ft_putstr_fd(S_SYNTAX, 2);
	if (code == EXTENSION)
		ft_putstr_fd(S_EXTENSION, 2);
	if (code == OPEN)
		ft_putstr_fd(S_OPEN, 2);
	if (code == WRONGARGS)
		ft_putstr_fd(S_WRONGARGS, 2);
	if (code == ACCESS)
		ft_putstr_fd(S_ACCESS, 2);
	if (code == MALLOC)
		ft_putstr_fd(S_MALLOC, 2);
	if (code == WRONGTEXTURE)
		ft_putstr_fd(S_WRONGTEXTURE, 2);
	return (-1);
}

int	img_error(int code, t_mlx_img *img)
{
	img->error = -1;
	if (code == IMAGE)
		ft_putstr_fd(S_IMAGE, 2);
	return (-1);
}
