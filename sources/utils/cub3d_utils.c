#include "cub3d.h"

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
