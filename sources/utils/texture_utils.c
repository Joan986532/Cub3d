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

static int	init_texture(t_texture *texture, void *mlx, char *path)
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

int	load_textures(t_global *global)
{
	global->north_texture = malloc(sizeof(t_texture));
	global->south_texture = malloc(sizeof(t_texture));
	global->east_texture = malloc(sizeof(t_texture));
	global->west_texture = malloc(sizeof(t_texture));
	if (!global->north_texture || !global->south_texture || 
		!global->east_texture || !global->west_texture)
		return (-1);
	if (init_texture(global->north_texture, global->data->mlx, global->map->north_t) < 0 ||
		init_texture(global->south_texture, global->data->mlx, global->map->south_t) < 0 ||
		init_texture(global->east_texture, global->data->mlx, global->map->east_t) < 0 ||
		init_texture(global->west_texture, global->data->mlx, global->map->west_t) < 0)
		return (-1);
	return (0);
}

void	free_textures(t_global *global)
{
	if (global->north_texture)
	{
		if (global->north_texture->img)
			mlx_destroy_image(global->data->mlx, global->north_texture->img);
		free(global->north_texture);
	}
	if (global->south_texture)
	{
		if (global->south_texture->img)
			mlx_destroy_image(global->data->mlx, global->south_texture->img);
		free(global->south_texture);
	}
	if (global->east_texture)
	{
		if (global->east_texture->img)
			mlx_destroy_image(global->data->mlx, global->east_texture->img);
		free(global->east_texture);
	}
	if (global->west_texture)
	{
		if (global->west_texture->img)
			mlx_destroy_image(global->data->mlx, global->west_texture->img);
		free(global->west_texture);
	}
}
