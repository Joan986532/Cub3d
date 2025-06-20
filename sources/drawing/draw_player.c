#include "cub3d.h"

void	rotate_antitrigo(t_player *player)
{
	float	x;

	x = player->fwd.x;
	player->fwd.x = player->fwd.x * cosf(player->angle)
		- player->fwd.y * sinf(player->angle);
	player->fwd.y = x * sinf(player->angle)
		+ player->fwd.y * cosf(player->angle);
	x = player->plane.x;
	player->plane.x = player->plane.x * cosf(player->angle)
		- player->plane.y * sinf(player->angle);
	player->plane.y = x * sinf(player->angle)
		+ player->plane.y * cosf(player->angle);
}

void	rotate_trigo(t_player *player)
{
	float	x;

	x = player->fwd.x;
	player->fwd.x = player->fwd.x * cosf(-player->angle)
		- player->fwd.y * sinf(-player->angle);
	player->fwd.y = x * sinf(-player->angle)
		+ player->fwd.y * cosf(-player->angle);
	x = player->plane.x;
	player->plane.x = player->plane.x * cosf(-player->angle)
		- player->plane.y * sinf(-player->angle);
	player->plane.y = x * sinf(-player->angle)
		+ player->plane.y * cosf(-player->angle);
}

void	choose_direction(t_player *player)
{
	if (player->forwd == 1)
	{
		player->pos.x += player->fwd.x * 0.1;
		player->pos.y += player->fwd.y * 0.1;
	}
	if (player->bckwd == 1)
	{
		player->pos.x -= player->fwd.x * 0.1;
		player->pos.y -= player->fwd.y * 0.1;
	}
	if (player->left)
	{
		player->pos.x -= player->plane.x * 0.1;
		player->pos.y -= player->plane.y * 0.1;
	}
	if (player->right)
	{
		player->pos.x += player->plane.x * 0.1;
		player->pos.y += player->plane.y * 0.1;
	}
}

void	pov_player(t_mlx_data *data, t_player *player)
{
	t_point		point;

	choose_direction(player);
	point.x1 = player->pos.x;
	point.y1 = player->pos.y;
	point.x2 = point.x1 + player->fwd.x * 10 + player->plane.x * 10;
	point.y2 = point.y1 + player->fwd.y * 10 + player->plane.y * 10;
	bresenham(&point, &data->view);
	point.x1 = point.x2;
	point.y1 = point.y2;
	point.x2 = point.x1 + player->fwd.x * 20 - player->plane.x * 10;
	point.y2 = point.y1 + player->fwd.y * 20 - player->plane.y * 10;
	bresenham(&point, &data->view);
	point.x1 = player->pos.x;
	point.y1 = player->pos.y;
	point.x2 = point.x1 + player->fwd.x * 10 - player->plane.x * 10;
	point.y2 = point.y1 + player->fwd.y * 10 - player->plane.y * 10;
	bresenham(&point, &data->view);
	point.x1 = point.x2;
	point.y1 = point.y2;
	point.x2 = point.x1 + player->fwd.x * 20 + player->plane.x * 10;
	point.y2 = point.y1 + player->fwd.y * 20 + player->plane.y * 10;
	bresenham(&point, &data->view);
}
