#include "cub3d_bonus.h"

void	print_tile(t_global *global, int x, int y, int color)
{
	int	i;
	int	j;
	int	size;

	j = 0;
	size = global->map->size;
	while (j < size)
	{
		i = 0;
		while (i < size)
		{
			my_pixel_put(&global->data->view, x * size + j,
				y * size + i, color);
			i++;
		}
		j++;
	}
}

int	draw_minimap(t_global *global)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (global->map->map[y])
	{
		x = 0;
		while (x < (int)ft_strlen(global->map->map[y]))
		{
			if (global->map->map[y][x] == '1')
				print_tile(global, x, y, 7237230);
			else
				print_tile(global, x, y, 16777215);
			x++;
		}
		y++;
	}
	return (0);
}
