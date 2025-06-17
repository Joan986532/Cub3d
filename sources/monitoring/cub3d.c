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
	map->size = 50;
	map->error = 0;
	map->player = player;
	player->pos = (t_vector3D){0, 0, 0};
	player->fwd = (t_vector3D){1, 0, 0};
	player->spawn = (t_vector3D){0, 0, 0};
	player->spawn_fwd = (t_vector3D){01, 0, 0};
	player->minimap_width = 100;
	player->minimap_height = 100;
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
	if (init_image(&data.view, data.mlx) == -1)
		return (1);
	mlx_key_hook(data.win, key_press, &global);
	mlx_loop_hook(data.mlx, render_frame, &global);
	mlx_hook(data.win, 17, 0, close_window, &global);
	mlx_loop(data.mlx);
}
