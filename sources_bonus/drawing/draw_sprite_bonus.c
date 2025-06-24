#include "cub3d_bonus.h"

int	draw_shooting_gun(t_player *player, t_mlx_data *data, t_global *global)
{
	int		color;
	float	x;
	float	y;
	float	scale;

	x = 0;
	scale = 0.25;
	while (x < 128)
	{
		y = 0;
		while (y < 128)
		{
			color = get_texture_color(global->pov_gun, x + player->shoot, y);
			if (color >= 0)
				my_pixel_put(&data->view, 1100 + (int)(x * 4),
					HEIGHT - 512 + (int)(y * 4), color);
			y += scale;
		}
		x += scale;
	}
	player->shoot += 128;
	if (player->shoot == 640)
		player->shoot = 0;
	return (0);
}

void	draw_idle(t_player *player, t_mlx_data *data, t_global *global)
{
	float	x;
	float	y;
	int		color;
	float	scale;

	x = 0;
	scale = 0.25;
	while (x < 128)
	{
		y = 0;
		while (y < 128)
		{
			color = get_texture_color(global->pov_gun, x, y);
			if (color >= 0)
				my_pixel_put(&data->view, 1100 + (int)(x * 4),
					HEIGHT - 512 + (int)(y * 4) - player->shoot, color);
			y += scale;
		}
		x += scale;
	}
	global->player->shoot -= 1;
	if (global->player->shoot == -25)
		global->player->shoot = 0;
}

int	draw_sprite(t_mlx_data *data, t_global *global)
{
	if (global->player->shoot > 0)
		draw_shooting_gun(global->player, data, global);
	else
		draw_idle(global->player, data, global);
	return (0);
}
