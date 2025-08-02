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

int	load_textures(t_global *global)
{
	char	*n_path;
	char	*s_path;
	char	*e_path;
	char	*w_path;
	char	*gun_path;

	n_path = global->map->north_t;
	s_path = global->map->south_t;
	e_path = global->map->east_t;
	w_path = global->map->west_t;
	gun_path = global->map->gun;
	global->north_texture = malloc(sizeof(t_texture));
	global->south_texture = malloc(sizeof(t_texture));
	global->east_texture = malloc(sizeof(t_texture));
	global->west_texture = malloc(sizeof(t_texture));
	global->door_texture = malloc(sizeof(t_texture));
	global->pov_gun = malloc(sizeof(t_texture));
	if (!global->north_texture ||!global->south_texture ||!global->east_texture
		|| !global->west_texture ||!global->pov_gun
		|| init_txt(global->north_texture, global->data->mlx, n_path)
		|| init_txt(global->south_texture, global->data->mlx, s_path)
		|| init_txt(global->east_texture, global->data->mlx, e_path)
		|| init_txt(global->west_texture, global->data->mlx, w_path)
		|| init_txt(global->door_texture, global->data->mlx, T_DOOR)
		|| init_txt(global->pov_gun, global->data->mlx, gun_path))
		return (-1);
	return (0);
}

void	check_and_clean_texture(t_texture *texture, void *mlx)
{
	if (!texture)
		return ;
	if (texture->img)
		mlx_destroy_image(mlx, texture->img);
	free(texture);
}

void	free_textures(t_global *global)
{
	check_and_clean_texture(global->north_texture, global->data->mlx);
	check_and_clean_texture(global->south_texture, global->data->mlx);
	check_and_clean_texture(global->east_texture, global->data->mlx);
	check_and_clean_texture(global->west_texture, global->data->mlx);
	check_and_clean_texture(global->door_texture, global->data->mlx);
	check_and_clean_texture(global->pov_gun, global->data->mlx);
}
