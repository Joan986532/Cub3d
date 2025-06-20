#include "cub3d.h"

void	init_ray(t_rat *ray, int x, t_global *global)
{
	t_player	*player;

	player = global->player;
	ray->cameraX = 2 * x / (double)WIDTH - 1;
	ray->rayDirX = player->fwd.x + player->plane.x * ray->cameraX;
	ray->rayDirY = player->fwd.y + player->plane.y * ray->cameraX;
	ray->mapX = (int)player->pos.x;
	ray->mapY = (int)player->pos.y;
	if (ray->rayDirX != 0)
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	else
		ray->deltaDistX = 1e30;
	if (ray->rayDirY != 0)
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	else
		ray->deltaDistY = 1e30;
	ray->hit = 0;
	ray->side = 0;
}

void	calculate_step(t_rat *ray, t_player *player)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (player->pos.x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - player->pos.x) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (player->pos.y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - player->pos.y) * ray->deltaDistY;
	}
}

void	perform_dda(t_rat *ray, t_global *global)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->mapX < -100 || ray->mapX > global->map->map_width + 100 ||
			ray->mapY < -100 || ray->mapY > global->map->map_height + 100)
		{
			ray->hit = 1;
			break;
		}
		if (ray->mapY < 0 || ray->mapX < 0 || ray->mapY >= global->map->map_height
			|| ray->mapX >= global->map->map_width)
			continue;
		if (global->map->map[ray->mapY][ray->mapX] == '1')
			ray->hit = 1;
	}
}