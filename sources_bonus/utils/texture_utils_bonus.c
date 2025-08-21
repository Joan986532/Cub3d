#include "cub3d_bonus.h"

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
	char	*paths[5];

	paths[0] = global->map->north_t;
	paths[1] = global->map->south_t;
	paths[2] = global->map->east_t;
	paths[3] = global->map->west_t;
	paths[4] = global->map->gun;
	set_texture_null(&global->north_texture);
	set_texture_null(&global->south_texture);
	set_texture_null(&global->east_texture);
	set_texture_null(&global->west_texture);
	set_texture_null(&global->door_texture);
	set_texture_null(&global->pov_gun);
	if (init_txt(&global->north_texture, global->data->mlx, paths[0])
		|| init_txt(&global->south_texture, global->data->mlx, paths[1])
		|| init_txt(&global->east_texture, global->data->mlx, paths[2])
		|| init_txt(&global->west_texture, global->data->mlx, paths[3])
		|| init_txt(&global->door_texture, global->data->mlx, T_DOOR)
		|| init_txt(&global->pov_gun, global->data->mlx, paths[4]))
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
	if (global->door_texture.img)
		mlx_destroy_image(global->data->mlx, global->door_texture.img);
	if (global->pov_gun.img)
		mlx_destroy_image(global->data->mlx, global->pov_gun.img);
}
