#include "cub3d.h"

int	init_mlx(t_mlx_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (data->win == NULL)
	{
		free(data->mlx);
		free(data->win);
		return (1);
	}
	return (0);
}

void	init_struct(t_datamap *map, t_global *global,
		t_player *player, t_mlx_data *data)
{
	map->map = NULL;
	map->map_height = 0;
	map->map_width = 0;
	map->north_t = NULL;
	map->south_t = NULL;
	map->east_t = NULL;
	map->west_t = NULL;
	map->floor = -1;
	map->ceiling = -1;
	map->global = global;
	map->size = 50;
	player->spawn_x = 16;
	player->spawn_y = 2;
	global->error = 0;
	global->player = player;
	global->map = map;
	global->data = data;
}

int	main(int argc, char **argv)
{
	t_mlx_data	data;
	t_datamap	map;
	t_global	global;
	t_player	player;

	init_struct(&map, &global, &player, &data);
	if (parsing(argv, argc, &map) == -1)
		return (1);
	if (init_mlx(&data))
		return (1);
	minimap(&data, &global);
	drawing(&data, &global);
	mlx_loop(data.mlx);
	free(map.north_t);
	free(map.south_t);
	free(map.east_t);
	free(map.west_t);
	free_arr(map.map);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
