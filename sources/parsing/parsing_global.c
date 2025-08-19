#include "cub3d.h"

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
		return (parsing_error(SYNTAX, map));
	if (map->error == -1)
		return (-1);
	return (0);
}

int	id_or_map(char *str, char *trimmed, t_datamap *map, int fd)
{
	if (ft_ismaj(trimmed[0]))
	{
		if (map_identifier(trimmed, map) == -1)
			return (-1);
	}
	else if (ft_isbin(trimmed[0]))
	{
		if (parse_map(str, map, fd) == -1)
			return (-1);
	}
	else if (trimmed[0] != '\n' && trimmed[0] != '\0')
		return (parsing_error(SYNTAX, map));
	return (0);
}

int	parser_line(int fd, t_datamap *map)
{
	char	*str;
	char	*trimmed;

	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		trimmed = str;
		while (*trimmed == ' ' || *trimmed == '\t')
			trimmed++;
		if (id_or_map(str, trimmed, map, fd) == -1)
			break ;
		free(str);
	}
	clear_gnl(str, fd);
	close(fd);
	if (map->error == -1)
	{
		clear_textures(map);
		free_arr(map->map);
		return (-1);
	}
	return (0);
}

int	parsing(char **argv, int argc, t_datamap *map)
{
	int	fd;

	if (argc != 2)
		return (parsing_error(WRONGARGS, map));
	if (parsing_extension(argv[1], map) == -1)
		return (-1);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (parsing_error(OPEN, map));
	if (parser_line(fd, map) == -1)
		return (-1);
	if (verify_struct(map) == -1)
		return (-1);
	return (0);
}
