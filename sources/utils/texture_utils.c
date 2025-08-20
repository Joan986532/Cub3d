#include "cub3d.h"

int	get_texture_color(t_texture *texture, int x, int y)
{
	char	*dst;
	int		color;

	if (x < 0 || y < 0 || x >= texture->width || y >= texture->height)
		return (0);
	dst = texture->addr + (y * texture->line_len + x * (texture->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

static int	init_txt(t_texture *texture, void *mlx, char *path)
{
	int	width;
	int	height;

	texture->img = mlx_xpm_file_to_image(mlx, path, &width, &height);
	if (!texture->img)
		return (-1);
	texture->width = width;
	texture->height = height;
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
		return (-1);
	return (0);
}

void	set_texture_null(t_texture *texture)
{
	texture->img = NULL;
	texture->addr = NULL;
}

int	load_textures(t_global *global)
{
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;

	n_path = global->map->north_t;
	s_path = global->map->south_t;
	e_path = global->map->east_t;
	w_path = global->map->west_t;
	set_texture_null(&global->north_texture);
	set_texture_null(&global->south_texture);
	set_texture_null(&global->east_texture);
	set_texture_null(&global->west_texture);
	if (init_txt(&global->north_texture, global->data->mlx, n_path)
		|| init_txt(&global->south_texture, global->data->mlx, s_path)
		|| init_txt(&global->east_texture, global->data->mlx, e_path)
		|| init_txt(&global->west_texture, global->data->mlx, w_path))
		return (-1);
	return (0);
}

void	free_textures(t_global *global)
{
	if (global->north_texture.img)
		mlx_destroy_image(global->data->mlx, global->north_texture.img);
	if (global->south_texture.img)
		mlx_destroy_image(global->data->mlx, global->south_texture.img);
	if (global->east_texture.img)
		mlx_destroy_image(global->data->mlx, global->east_texture.img);
	if (global->west_texture.img)
		mlx_destroy_image(global->data->mlx, global->west_texture.img);
}
