#include "cub3d.h"
// 
// void	print_tile(t_mlx_data *data, int x, int y, int color)
// {
	// int	i;
	// int	j;
	// int	size;
// 
	// size = 10;
	// j = 0;
	// while (j < size)
	// {
		// i = 0;
		// while (i < size)
		// {
			// my_pixel_put(&data->view, x * size + j,
				// y * size + i, color);
			// i++;
		// }
		// j++;
	// }
// }
// 
// int	draw_minimap(t_player *player, t_datamap *map, t_mlx_data *data)
// {
	// int		x;
	// int		y;
// 
	// x = 0;
	// y = 0;
	// (void)player;
	// while (map->map[y])
	// {
		// x = 0;
		// while (x < (int)ft_strlen(map->map[y]))
		// {
			// if (map->map[y][x] == '1')
				// print_tile(global, x, y, 7237230);
			// else
				// print_tile(global, x, y, 16777215);
			// x++;
		// }
		// y++;
	// }
	// return (0);
// }

int	draw_minimap(t_datamap *map, t_mlx_data *data)
{
	float	x;
	float	y;
	float	scale;
	int		size;

	y = 0;
	scale = 0.1000001;
	size = ft_strlen(map->map[(int)y]);
	while (map->map[(int)y])
	{
		x = 0;
		while (x < size)
		{
			if (map->map[(int)y][(int)x] == '1')
				my_pixel_put(&data->view, x * 10, y * 10, 0x000000);
			else if (map->map[(int)y][(int)x] == '0')
				my_pixel_put(&data->view, x * 10, y * 10, 0xFFFFFF);
			x += scale;
		}
		y += scale;
	}
	return (0);
}


