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

void	choose_direction(t_player *player)
{
	if (player->forwd == 1)
	{
		player->pos.x += player->fwd.x * 0.08;
		player->pos.y += player->fwd.y * 0.08;
	}
	if (player->bckwd == 1)
	{
		player->pos.x -= player->fwd.x * 0.08;
		player->pos.y -= player->fwd.y * 0.08;
	}
	if (player->left)
	{
		player->pos.x -= player->plane.x * 0.08;
		player->pos.y -= player->plane.y * 0.08;
	}
	if (player->right)
	{
		player->pos.x += player->plane.x * 0.08;
		player->pos.y += player->plane.y * 0.08;
	}
}

void	pov_player(t_mlx_data *data, t_player *player)
{
	t_point		point;

	choose_direction(player);
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
