#include "cub3d_bonus.h"

void	rotate_antitrigo(t_player *player, float angle)
{
	float	x;

	x = player->fwd.x;
	player->fwd.x = player->fwd.x * cosf(angle)
		- player->fwd.y * sinf(angle);
	player->fwd.y = x * sinf(angle)
		+ player->fwd.y * cosf(angle);
	x = player->plane.x;
	player->plane.x = player->plane.x * cosf(angle)
		- player->plane.y * sinf(angle);
	player->plane.y = x * sinf(angle)
		+ player->plane.y * cosf(angle);
}

void	rotate_trigo(t_player *player, float angle)
{
	float	x;

	x = player->fwd.x;
	player->fwd.x = player->fwd.x * cosf(-angle)
		- player->fwd.y * sinf(-angle);
	player->fwd.y = x * sinf(-angle)
		+ player->fwd.y * cosf(-angle);
	x = player->plane.x;
	player->plane.x = player->plane.x * cosf(-angle)
		- player->plane.y * sinf(-angle);
	player->plane.y = x * sinf(-angle)
		+ player->plane.y * cosf(-angle);
}

int		is_available_space(float x, float y, t_datamap *map)
{
	int		posx;
	int		posy;

	posx = (int)x;
	posy = (int)y;
	if (posx < 0 || posx >= map->map_width || posy < 0 || posy >= map->map_height)
		return (0);
	return (map->map[posy][posx] == '0');
}

void	choose_direction(t_player *player, t_datamap *map)
{
	float	step;
	float	new_x;
	float	new_y;
	
	step = 0.08;
	if (player->forwd == 1)
	{
		new_x = player->pos.x + player->fwd.x * step;
		new_y = player->pos.y + player->fwd.y * step;
		if (is_available_space(new_x, player->pos.y, map))
			player->pos.x = new_x;
		if (is_available_space(player->pos.x, new_y, map))
			player->pos.y = new_y;
	}
	if (player->bckwd == 1)
	{
		new_x = player->pos.x - player->fwd.x * step;
		new_y = player->pos.y - player->fwd.y * step;
		if (is_available_space(new_x, player->pos.y, map))
			player->pos.x = new_x;
		if (is_available_space(player->pos.x, new_y, map))
			player->pos.y = new_y;
	}
	if (player->left)
	{
		new_x = player->pos.x - player->plane.x * step;
		new_y = player->pos.y - player->plane.y * step;
		if (is_available_space(new_x, player->pos.y, map))
			player->pos.x = new_x;
		if (is_available_space(player->pos.x, new_y, map))
			player->pos.y = new_y;
	}
	if (player->right)
	{
		new_x = player->pos.x + player->plane.x * step;
		new_y = player->pos.y + player->plane.y * step;
		if (is_available_space(new_x, player->pos.y, map))
			player->pos.x = new_x;
		if (is_available_space(player->pos.x, new_y, map))
			player->pos.y = new_y;
	}
}

void	pov_player(t_mlx_data *data, t_player *player, t_datamap *map)
{
	t_point		point;

	choose_direction(player, map);
	point.x1 = player->pos.x * 10;
	point.y1 = player->pos.y * 10;
	point.x2 = point.x1 + 5 * (player->fwd.x + player->plane.x);
	point.y2 = point.y1 + 5 * (player->fwd.y + player->plane.y);
	bresenham(&point, &data->view);
	point.x1 = point.x2;
	point.y1 = point.y2;
	point.x2 = point.x1 + 5 * (2 * player->fwd.x - player->plane.x);
	point.y2 = point.y1 + 5 * (2 * player->fwd.y - player->plane.y);
	bresenham(&point, &data->view);
	point.x1 = player->pos.x * 10;
	point.y1 = player->pos.y * 10;
	point.x2 = point.x1 + 5 * (player->fwd.x - player->plane.x);
	point.y2 = point.y1 + 5 * (player->fwd.y - player->plane.y);
	bresenham(&point, &data->view);
	point.x1 = point.x2;
	point.y1 = point.y2;
	point.x2 = point.x1 + 5 * (2 * player->fwd.x + player->plane.x);
	point.y2 = point.y1 + 5 * (2 * player->fwd.y + player->plane.y);
	bresenham(&point, &data->view);
}
