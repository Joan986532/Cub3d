#include "cub3d_bonus.h"

int	close_window(void *data)
{
	t_global	*global;

	global = data;
	free_textures(global);
	free(global->map->north_t);
	free(global->map->south_t);
	free(global->map->east_t);
	free(global->map->west_t);
	free(global->map->gun);
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
	float		diff_x;
	float		diff_y;

	diff_x = fabs((float)(WIDTH / 2) - (float)x);
	diff_x *= M_PI / 5000;
	diff_y = (float)(HEIGHT / 2) - (float)y;
	global->player->fwd.z += diff_y * 180 / HEIGHT;
	if (global->player->fwd.z > 90)
		global->player->fwd.z = 90;
	if (global->player->fwd.z < -90)
		global->player->fwd.z = -90;
	if (old_x > x)
		rotate_trigo(global->player, diff_x);
	else if (old_x < x)
		rotate_antitrigo(global->player, diff_x);
	mlx_mouse_move(global->data->mlx, global->data->win, WIDTH / 2, HEIGHT / 2);
	old_x = x;
	return (0);
}

int	shoot_gun(int	button, int x, int y, t_global *global)
{
	(void)button;
	(void)x;
	(void)y;
	global->player->shoot = 128;
	return (0);
}
