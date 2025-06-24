#include "cub3d.h"

void	choose_color_tile(t_datamap *map, t_mlx_data *data,
		t_vector2D point, t_vector2D corner)
{
	float	x;
	float	y;

	x = point.x / 10 + corner.x;
	y = point.y / 10 + corner.y;
	if (x >= 0 && x < map->map_width && y >= 0 && y < map->map_height)
	{
		if (map->map[(int)y][(int)x] == '0')
			my_pixel_put(&data->view, point.x, point.y, 0xFFFFFF);
		else if (map->map[(int)y][(int)x] == '1')
			my_pixel_put(&data->view, point.x, point.y, 0x000000);
		else
			my_pixel_put(&data->view, point.x, point.y, map->floor);
	}
	else
		my_pixel_put(&data->view, point.x, point.y, map->floor);
}

int	draw_minimap(t_datamap *map, t_player *player, t_mlx_data *data)
{
	t_vector2D	point;
	t_vector2D	corner;

	point.x = 0;
	point.y = 0;
	corner.x = player->pos.x - 10;
	corner.y = player->pos.y - 10;
	while (point.y < 200)
	{
		point.x = 0;
		while (point.x < 200)
		{
			choose_color_tile(map, data, point, corner);
			point.x++;
		}
		point.y++;
	}
	return (0);
}
