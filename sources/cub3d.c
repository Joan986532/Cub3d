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

int	main(int argc, char **argv)
{
	t_mlx_data	data;

	if (init_mlx(&data, argc))
		return (1);
	if (map_parsing(argv, argc) == -1)
	{
		free(data.mlx);
		free(data.win);
		return (1);
	}
}
