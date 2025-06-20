#include "cub3d.h"

int	close_window(void *data)
{
	t_global	*global;

	global = data;
	free(global->map->north_t);
	free(global->map->south_t);
	free(global->map->east_t);
	free(global->map->west_t);
	free_arr(global->map->map);
	mlx_destroy_image(global->data->mlx, global->data->view.mlx_img);
	mlx_destroy_window(global->data->mlx, global->data->win);
	mlx_destroy_display(global->data->mlx);
	free(global->data->mlx);
	exit(0);
	return (0);
}

int	key_release(int keysym, t_global *global)
{
	if (keysym == XK_w)
		global->player->forwd = 0;
	if (keysym == XK_s)
		global->player->bckwd = 0;
	if (keysym == XK_a)
		global->player->left = 0;
	if (keysym == XK_d)
		global->player->right = 0;
	return (0);
}

int	key_press(int keysym, t_global *global)
{
	if (keysym == XK_w)
		global->player->forwd = 1;
	if (keysym == XK_s)
		global->player->bckwd = 1;
	if (keysym == XK_a)
		global->player->left = 1;
	if (keysym == XK_d)
		global->player->right = 1;
	if (keysym == XK_Escape)
		close_window(global);
	return (0);
}

int	mouse_moove(int x, int y, t_global *global)
{
	static int	old_x;

	(void)y;
	if (old_x > x)
		rotate_antitrigo(global->player);
	else if (old_x < x)
		rotate_trigo(global->player);
	old_x = x;
	return (0);
}
