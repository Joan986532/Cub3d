#include "cub3d.h"

int	is_texture_ok(char c1, char c2, char *str, t_datamap *map)
{
	if (c1 == 'E' && c2 == 'A' && map->east_t == NULL)
	{
		map->east_t = ft_strjoin(NULL, str);
		if (!map->east_t)
			return (parsing_error(MALLOC, map));
	}
	else if (c1 == 'W' && c2 == 'E' && map->west_t == NULL)
	{
		map->west_t = ft_strjoin(NULL, str);
		if (!map->west_t)
			return (parsing_error(MALLOC, map));
	}
	return (0);
}

int	choose_texture_surface(char c1, char c2, char *str, t_datamap *map)
{
	if (c1 == 'N' && c2 == 'O' && map->north_t == NULL)
	{
		map->north_t = ft_strjoin(NULL, str);
		if (!map->north_t)
			return (parsing_error(MALLOC, map));
	}
	else if (c1 == 'S' && c2 == 'O' && map->south_t == NULL)
	{
		map->south_t = ft_strjoin(NULL, str);
		if (!map->south_t)
			return (parsing_error(MALLOC, map));
	}
	else if (is_texture_ok(c1, c2, str, map) == -1)
		return (-1);
	return (0);
}

int	remove_backn(char *str, t_datamap *map)
{
	int	i;

	i = 0;
	while (str[i] != ' ' && str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
	while (str[i] != '\0' && str[i] != '\n')
	{
		if (str[i] != ' ')
			return (parsing_error(SYNTAX, map));
		i++;
	}
	return (0);
}

int	istexture_valid(char *str, t_datamap *map)
{
	if (str[0] == '.' && str[1] == '/' && str[2] != '/')
	{
		if (remove_backn(str, map) == -1)
			return (-1);
		if (access(str, O_RDONLY) == -1)
			return (parsing_error(ACCESS, map));
	}
	else
		return (parsing_error(SYNTAX, map));
	return (0);
}

int	istexture(char *str, t_datamap *map)
{
	int		i;

	i = 2;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (i == 2)
		return (parsing_error(SYNTAX, map));
	if (str[i] != '.' && str[i + 1] != '/')
		return (parsing_error(SYNTAX, map));
	if (istexture_valid(&str[i], map) == -1)
		return (-1);
	if (choose_texture_surface(str[0], str[1], &str[i + 2], map) == -1)
		return (-1);
	return (0);
}
