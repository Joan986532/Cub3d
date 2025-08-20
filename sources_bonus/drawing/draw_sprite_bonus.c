#include "cub3d_bonus.h"

void	draw_crosshair(t_mlx_data *data)
{
	int	x;
	int	y;

	y = 470;
	x = 960;
	while (y < 610)
	{
		if (y < 515 || y > 565)
			my_pixel_put(&data->view, x, y, 0xFFFFFF);
		y++;
	}
	y = 540;
	x = 890;
	while (x < 1030)
	{
		if (x < 935 || x > 985)
			my_pixel_put(&data->view, x, y, 0xFFFFFF);
		x++;
	}
}

int	init_shooting_gun(t_player *player, t_mlx_data *data, t_global *global)
{
	unsigned long	actualtime;

	actualtime = gettime_ms();
	if (actualtime > global->timeofday + 50 && player->shoot == 128)
		player->shoot += 128;
	else if (actualtime > global->timeofday + 100 && player->shoot == 256)
		player->shoot += 128;
	else if (actualtime > global->timeofday + 150 && player->shoot == 384)
		player->shoot += 128;
	else if (actualtime > global->timeofday + 200 && player->shoot == 512)
		player->shoot += 128;
	if (player->shoot == 640)
		player->shoot = 0;
	draw_shooting_gun(player, data, global);
	return (0);
}

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
			color = get_texture_color(&global->pov_gun, x + player->shoot, y);
			if (color >= 0)
				my_pixel_put(&data->view, 1100 + (int)(x * 4),
					HEIGHT - 575 + (int)(y * 4), color);
			y += scale;
		}
		x += scale;
	}
	return (0);
}

void	draw_idle(t_player *player, t_mlx_data *data, t_global *global)
{
	double	x;
	double	y;
	int		color;
	float	scale;

	x = 0;
	scale = 0.25;
	while (x < 128)
	{
		y = 0;
		while (y < 128)
		{
			color = get_texture_color(&global->pov_gun, x, y);
			if (color >= 0)
				my_pixel_put(&data->view, 1100 + (int)(x * 4),
					HEIGHT - 575 + (int)(y * 4) - player->shoot, color);
			y += scale;
		}
		x += scale;
	}
}

int	draw_sprite(t_mlx_data *data, t_global *global)
{
	static int		flag;

	if (global->player->shoot > 0)
	{
		init_shooting_gun(global->player, data, global);
		flag = 0;
	}
	else
	{
		if (flag == 0 || flag == 1)
			draw_idle(global->player, data, global);
		if (flag == 0)
			global->player->shoot--;
		else if (flag == 1)
			global->player->shoot++;
		if (global->player->shoot == -25)
			flag = 1;
		else if (global->player->shoot == 0)
			flag = 0;
	}
	draw_crosshair(data);
	return (0);
}
