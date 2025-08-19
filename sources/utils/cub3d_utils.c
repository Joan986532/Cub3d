#include "cub3d.h"

int	free_levels(int level, t_global *global)
{
	if (level >= 4)
		free_textures(global);
	if (level >= 3)
		mlx_destroy_image(global->data->mlx, global->data->view.mlx_img);
	if (level >= 2)
	{
		if (global->data->win)
			mlx_destroy_window(global->data->mlx, global->data->win);
		if (global->data->mlx)
			mlx_destroy_display(global->data->mlx);
		free(global->data->mlx);
		clear_textures(global->map);
		free_arr(global->map->map);
	}
	return (1);
}

void	clear_gnl(char *str, int fd)
{
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		if (!str)
			break ;
	}
	free (str);
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_strtrime(char *str)
{
	int	i;
	int	j;

	if (!str)
		return ;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	j = ft_strlen(str) - 1;
	while (j > i && (str[j] == ' ' || str[j] == '\t'))
		j--;
	ft_memmove(str, str + i, j - i + 1);
	str[j - i + 1] = '\0';
}

void	clear_textures(t_datamap *map)
{
	if (map->north_t)
		free(map->north_t);
	if (map->south_t)
		free(map->south_t);
	if (map->east_t)
		free(map->east_t);
	if (map->west_t)
		free(map->west_t);
}
