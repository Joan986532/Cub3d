#include "cub3d_bonus.h"

int	init_mlx(t_mlx_data *data)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "Cub3D");
	if (data->win == NULL)
		return (1);
	return (0);
}

void	init_player(t_player *player)
{
	player->pos = (t_vector3D){0, 0, 0};
	player->fwd = (t_vector3D){1, 0, 0};
	player->spawn = (t_vector3D){0, 0, 0};
	player->spawn_fwd = (t_vector3D){1, 0, 0};
	player->minimap_width = 100;
	player->minimap_height = 100;
	player->max_render_distance = 100;
	player->bckwd = 0;
	player->forwd = 0;
	player->left = 0;
	player->right = 0;
	player->trnleft = 0;
	player->trnright = 0;
	player->shoot = 0;
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
	map->gun = NULL;
	map->floor = -1;
	map->ceiling = -1;
	map->size = 10;
	map->error = 0;
	map->player = player;
	init_player(player);
	global->error = 0;
	global->player = player;
	global->map = map;
	global->data = data;
	global->press = 0;
}

void	setup_hooks(void *win, void *mlx, t_global *global)
{
	mlx_hook(win, KeyPress, KeyPressMask, &key_press, global);
	mlx_hook(win, KeyRelease, KeyReleaseMask, &key_release, global);
	mlx_hook(win, MotionNotify, PointerMotionMask, &mouse_moove, global);
	mlx_hook(win, ButtonPress, ButtonPressMask, &shoot_gun, global);
	mlx_mouse_hide(mlx, win);
	mlx_hook(win, DestroyNotify, StructureNotifyMask, &close_window, global);
	mlx_loop_hook(mlx, render_frame, global);
}

int	main(int argc, char **argv)
{
	t_mlx_data	data;
	t_datamap	map;
	t_global	global;
	t_player	player;

	init_struct(&map, &global, &player, &data);
	if (parsing(argv, argc, &map) == -1)
		return (free_levels(1, &global));
	if (init_mlx(&data))
		return (free_levels(2, &global));
	if (init_minimap(&global, &data, &map))
		return (free_levels(3, &global));
	if (init_image(&data.view, data.mlx) == -1)
		return (free_levels(4, &global));
	if (load_textures(&global) == -1)
		return (free_levels(5, &global));
	setup_hooks(data.win, data.mlx, &global);
	mlx_loop(global.data->mlx);
	free_textures(&global);
	return (0);
}
