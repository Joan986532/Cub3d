#include "cub3d.h"

static int is_spawn(char c)
{
    if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
        return (1);
    return (0);
}

static int is_whitlisted_char(char c)
{
    if (is_spawn(c) || c == '0' || c == '1')
        return (1);
    return (0);
}

static int is_border(int x, int y, int height, int width)
{
    if (x == 0 || x == height - 1 || y == 0 || y == width - 1)
        return (1);
    return (0);
}


static int  is_valid_line(char *line, int i, int *spawn_found, int map_height)
{
    int j;

    j = 0;
    while (line[j])
    {
        if (is_whitlisted_char(line[j]))
        {
            if (*spawn_found && is_spawn(line[j]))
                return (-1);
            if (is_spawn(line[j]))
                *spawn_found = 1;
            if (is_border(i, j, map_height, ft_strlen(line)) && line[j] != '1')
                return (-1);
        }
        else
            return (-1);
        j++;
    }
    return (0);
}

int is_valid_map(char **map, int map_height)
{
    int i;
    int spawn_found;

	if (!map)
		return (-1);
    spawn_found = 0;
    i = 0;
    while (map[i])
    {
        if (is_valid_line(map[i], i, &spawn_found, map_height) == -1)
            return (-1);
        i++;
    }
	return (0);
}
