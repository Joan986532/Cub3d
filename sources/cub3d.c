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

void	init_struct(t_datamap *map, t_global *global)
{
	map->north_t = NULL;
	map->south_t = NULL;
	map->east_t = NULL;
	map->west_t = NULL;
	map->floor = -1;
	map->ceiling = -1;
	map->global = global;
	global->error = 0;
}

int	main(int argc, char **argv)
{
	t_mlx_data	data;
	t_datamap	map;
	t_global	global;

	init_struct(&map, &global);
	if (parsing(argv, argc, &map) == -1)
		return (1);
	free(map.north_t);
	free(map.south_t);
	free(map.east_t);
	free(map.west_t);
	if (init_mlx(&data))
		return (1);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
