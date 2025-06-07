#include "headers/cub3d.h"

//identifier
int	map_identifier(char *str, t_datamap *map)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (ft_ismaj(str[i]))
			i++;
		if (i == 1)
			iscolor(str, map);
		// else if (i == 2)
			// istexture(str, map);
		else
		{
			return (parsing_error(SYNTAX, map->global));
		}
		if (map->global->error == -1)
			return (-1);
	}
	return (0);
}

//global
int	parser_line(int fd, t_datamap *map)
{
	char	*str;
	int		i;

	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		while (str[i] == ' ')
			i++;
		if (ft_ismaj(str[i]))
			if (map_identifier(&str[i], map) == -1)
				break ;
		if (ft_isbin(str[i]))
			// if (map_parser(&str[i], map) == -1)
				break ;
		if (str[i] != '\n' && str[i] != '\0')
			break ;
		free(str);
	}
	free(str);
	if (map->global->error == -1)
		return (-1);
	return (0);
}

int map_parsing(char **argv, int argc, t_datamap *map)
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
	return (0);
}
