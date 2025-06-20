#include "cub3d.h"

int	verify_struct(t_datamap *map)
{
	if (map->ceiling == -1 || map->floor == -1)
	{
		clear_textures(map);
		return (parsing_error(WRONGCOLOR, map));
	}
	if (map->north_t == NULL || map->south_t == NULL
		|| map->east_t == NULL || map->west_t == NULL)
	{
		clear_textures(map);
		return (parsing_error(WRONGTEXTURE, map));
	}
	if (is_valid_map(map->map) == -1)
	{
		clear_textures(map);
		return (parsing_error(SYNTAX, map));
	}
	return (0);
}

int	parsing_extension(char *str, t_datamap *map)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '.')
		i++;
	if (str[i])
	{
		tmp = &str[i];
		tmp = ft_strnstr(tmp, ".cub", 4);
		if (!tmp || tmp[4] != '\0')
			return (parsing_error(EXTENSION, map));
		else
			return (0);
	}
	return (parsing_error(EXTENSION, map));
}
