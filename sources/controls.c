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

void	rotate_antitrigo(t_player *player)
{
	float	x;

	x = player->fwd.x;
	player->fwd.x = player->fwd.x * cosf(player->angle)
		- player->fwd.y * sinf(player->angle);
	player->fwd.y = x * sinf(player->angle)
		+ player->fwd.y * cosf(player->angle);
}

void	rotate_trigo(t_player *player)
{
	float	x;

	x = player->fwd.x;
	player->fwd.x = player->fwd.x * cosf(-player->angle)
		- player->fwd.y * sinf(-player->angle);
	player->fwd.y = x * sinf(-player->angle)
		+ player->fwd.y * cosf(-player->angle);
}

int	key_press(int keysym, t_global *global)
{
	if (keysym == XK_w)
	{
		global->player->pos.x += global->player->fwd.x * 5;
		global->player->pos.y += global->player->fwd.y * 5;
	}
	if (keysym == XK_s)
	{
		global->player->pos.x -= global->player->fwd.x * 5;
		global->player->pos.y -= global->player->fwd.y * 5;
	}
	if (keysym == XK_a)
		rotate_trigo(global->player);
	if (keysym == XK_d)
		rotate_antitrigo(global->player);
	if (keysym == XK_Escape)
		close_window(global);
	return (0);
}
