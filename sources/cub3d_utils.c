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
