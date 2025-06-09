#include "headers/cub3d.h"

int	choose_texture_surface(char c1, char c2, char *str, t_datamap *map)
{
	if (c1 == 'N' && c2 == 'O')
	{
		map->north_t = ft_strjoin(NULL, str);
		if (!map->north_t)
			return (parsing_error(MALLOC, map->global));
	}
	else if (c1 == 'S' && c2 == 'O')
	{
		map->south_t = ft_strjoin(NULL, str);
		if (!map->south_t)
			return (parsing_error(MALLOC, map->global));
	}
	else if (c1 == 'E' && c2 == 'A')
	{
		map->east_t = ft_strjoin(NULL, str);
		if (!map->east_t)
			return (parsing_error(MALLOC, map->global));
	}
	else if (c1 == 'W' && c2 == 'E')
	{
		map->west_t = ft_strjoin(NULL, str);
		if (!map->west_t)
			return (parsing_error(MALLOC, map->global));
	}
	return (0);
}

int	remove_backn(char *str, t_datamap *map)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
		i++;
	while (str[i] == ' ')
	{
		str[i] = '\0';
		i++;
	}
	if (str[i] == '\n')
		str[i] = '\0';
	else if (str[i] != '\0')
	{
		return (parsing_error(SYNTAX, map->global));
	}
	return (0);
}

int	istexture_valid(char *str, t_datamap *map)
{
	if (remove_backn(&str[i + 2], map) == -1)
		return (-1);
	if (access(&str[i + 2], O_RDONLY) == -1)
	{
		clear_textures(map);
		return (parsing_error(ACCESS, map->global));
	}
	return (0);
}

int	istexture(char *str, t_datamap *map)
{
	int		i;
	char	*tmp;

	i = 2;
	tmp = NULL;
	while (str[i] && str[i] == ' ')
		i++;
	if (i == 2)
		return (parsing_error(SYNTAX, map->global));
	if (str[i] != '.' && str[i + 1] != '/')
		return (parsing_error(SYNTAX, map->global));
	if (istexture_valid(&str[i + 2], map) == -1)
		return (-1);
	if (choose_texture_surface(str[0], str[1], &str[i + 2], map) == -1)
	{
		clear_textures(map);
		return (-1);
	}
	return (0);
}
