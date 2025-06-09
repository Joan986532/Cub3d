#include "headers/cub3d.h"

int	init_mlx(t_mlx_data *data, int argc)
{
	if (argc != 2)
		return (1);
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
	map->floor = 0;
	map->ceiling = 0;
	map->global = global;
	global->error = 0;
}

int	main(int argc, char **argv)
{
	t_mlx_data	data;
	t_datamap	map;
	t_global	global;

	if (init_mlx(&data, argc))
		return (1);
	init_struct(&map, &global);
	if (map_parsing(argv, argc, &map) == -1)
	{
		mlx_destroy_window(data.mlx, data.win);
		mlx_destroy_display(data.mlx);
		free(data.mlx);
		// free(data.win);
		return (1);
	}
	printf("F: %d\n", map.floor);
	printf("C: %d\n", map.ceiling);
	printf("NO: %s\n", map.north_t);
	printf("SO: %s\n", map.south_t);
	printf("EA: %s\n", map.east_t);
	printf("WE: %s\n", map.west_t);
	free(map.north_t);
	free(map.south_t);
	free(map.east_t);
	free(map.west_t);
	mlx_destroy_window(data.mlx, data.win);
	mlx_destroy_display(data.mlx);
	free(data.mlx);
}
