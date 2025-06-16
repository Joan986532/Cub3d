#include "cub3d.h"

int		close_window(void *data)
{
	t_global	*global;

	global = data;
	free(global->map->north_t);
	free(global->map->south_t);
	free(global->map->east_t);
	free(global->map->west_t);
	free_arr(global->map->map);
	mlx_destroy_image(global->data->mlx, global->data->img.mlx_img);
	mlx_destroy_window(global->data->mlx, global->data->win);
	mlx_destroy_display(global->data->mlx);
	free(global->data->mlx);
	exit(1);
}

int	key_press(int keysym, t_global *global)
{
	if (keysym == XK_w)
		global->player->pos.y -= 2;
	if (keysym == XK_s)
		global->player->pos.y += 2;
	if (keysym == XK_a)
		global->player->pos.x -= 2;
	if (keysym == XK_d)
		global->player->pos.x += 2;
	if (keysym == XK_Escape)
		close_window(global);
	return (0);
}
