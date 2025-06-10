#include "headers/cub3d.h"

//identifier
int	map_identifier(char *str, t_datamap *map)
{
	int	i;

	i = 0;
	while (ft_ismaj(str[i]))
		i++;
	if (i == 1)
		iscolor(str, map);
	else if (i == 2)
		istexture(str, map);
	else
		return (parsing_error(SYNTAX, map->global));
	if (map->global->error == -1)
		return (-1);
	return (0);
}

int	id_or_map(char *str, t_datamap *map)
{
	int	i;

	i = 0;
	if (ft_ismaj(str[i]))
	{
		if (map_identifier(&str[i], map) == -1)
			return (-1);
	}
	// if (ft_isbin(str[i]))
//	{
		// if (map_parser(&str[i], map) == -1)
		// break ;
//	}
	else if (str[i] != '\n' && str[i] != '\0')
		return (parsing_error(SYNTAX, map->global));
	return (0);
}

//global
int	parser_line(int fd, t_datamap *map)
{
	char	*str;
	int		i;

	while (1)
	{
		i = 0;
		str = get_next_line(fd);
		if (!str)
			break ;
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		if (id_or_map(&str[i], map) == -1)
			break ;
		free(str);
	}
	clear_gnl(str, fd);
	close(fd);
	if (map->global->error == -1)
	{
		clear_textures(map);
		return (-1);
	}
	return (0);
}

int	verify_struct(t_datamap *map)
{
	if (map->ceiling == -1 || map->floor == -1)
	{
		clear_textures(map);
		return (parsing_error(WRONGCOLOR, map->global));
	}
	if (map->north_t == NULL || map->south_t == NULL
		|| map->east_t == NULL || map->west_t == NULL)
	{
		clear_textures(map);
		return (parsing_error(WRONGTEXTURE, map->global));
	}
	return (0);
}

int	map_parsing(char **argv, int argc, t_datamap *map)
{
	int	fd;

	if (argc != 2)
		return (parsing_error(WRONGARGS, map->global));
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
		return (parsing_error(EXTENSION, map->global));
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (parsing_error(OPEN, map->global));
	if (parser_line(fd, map) == -1)
		return (-1);
	if (verify_struct(map) == -1)
		return (-1);
	return (0);
}
