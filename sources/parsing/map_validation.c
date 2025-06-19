#include "cub3d.h"

int is_spawn(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (1);
	return (0);
}

static int is_whitlisted_char(char c)
{
	if (is_spawn(c) || c == '0' || c == '1' || c == ' ')
		return (1);
	return (0);
}

static int is_well_surrounded(char **map, int i, int j)
{
	if (i == 0 || j == 0 || j == (int)ft_strlen(map[i]) - 1 || !map[i + 1])
		return (-1);
	if (map[i][j - 1] == ' ' || map[i][j + 1] == ' ')
		return (-1);
	if (map[i + 1][j] == ' ' || map[i - 1][j] == ' ')
		return (-1);
	return (0);
}

static int  is_cell_valid(char **map, int i, int j, int *spawn_found)
{
	if (!is_whitlisted_char(map[i][j]))
		return (-1);
	if (is_spawn(map[i][j]))
	{
		(*spawn_found)++;
		map[i][j] = '0';
	}
	if (map[i][j] == '1' || map[i][j] == ' ')
		return (0);
	if (is_well_surrounded(map, i, j) == -1)
		return (-1);
	return (0);
}

int is_valid_map(char **map)
{
	int i;
	int j;
	int spawn_found;

	if (!map)
		return (-1);
	spawn_found = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_cell_valid(map, i, j, &spawn_found) == -1)
				return (-1);
			j++;
		}
		i++;
	}
	if (spawn_found != 1)
		return (-1);
	return (0);
}
