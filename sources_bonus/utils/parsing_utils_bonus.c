#include "cub3d_bonus.h"

int	verify_struct_bonus(t_datamap *map)
{
	if (map->ceiling == -1 || map->floor == -1)
	{
		clear_textures(map);
		return (parsing_error(WRONGCOLOR, map));
	}
	if (map->north_t == NULL || map->south_t == NULL
		|| map->east_t == NULL || map->west_t == NULL
		|| map->gun == NULL)
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

char	*get_next_line_no_nl(int fd)
{
	char	*str;
	int		i;

	str = get_next_line(fd);
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	str[i] = '\0';
	return (str);
}

void	set_spawn(t_player *player, char c, int i, int j)
{
	player->spawn = (t_vector3D){j + 0.5, i + 0.5, 0};
	player->pos = player->spawn;
	if (c == 'N')
	{
		player->spawn_fwd = (t_vector3D){0, -1, 0};
		player->plane = (t_vector3D){1, 0, 0};
	}
	else if (c == 'S')
	{
		player->spawn_fwd = (t_vector3D){0, 1, 0};
		player->plane = (t_vector3D){-1, 0, 0};
	}
	else if (c == 'E')
	{
		player->spawn_fwd = (t_vector3D){1, 0, 0};
		player->plane = (t_vector3D){0, 1, 0};
	}
	else if (c == 'W')
	{
		player->spawn_fwd = (t_vector3D){-1, 0, 0};
		player->plane = (t_vector3D){0, -1, 0};
	}
	player->fwd = player->spawn_fwd;
	player->angle = M_PI / 64;
}

void	set_map_dimensions(t_list *linked_map, t_datamap *map)
{
	int	current_width;
	int	width;
	int	height;

	width = 0;
	height = 0;
	while (linked_map)
	{
		current_width = ft_strlen((char *)linked_map->content);
		if (current_width > width)
			width = current_width;
		++height;
		linked_map = linked_map->next;
	}
	map->map_width = width;
	map->map_height = height;
}
