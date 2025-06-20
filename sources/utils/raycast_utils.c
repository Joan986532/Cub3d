#include "cub3d.h"

void	init_ray(t_rat *ray, int x, t_global *global)
{
	ray->cameraX = 2 * x / (double)WIDTH - 1;
	ray->rayDirX = global->player->fwd.x + global->player->plane.x * ray->cameraX;
	ray->rayDirY = global->player->fwd.y + global->player->plane.y * ray->cameraX;
	ray->mapX = (int)global->player->pos.x;
	ray->mapY = (int)global->player->pos.y;
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
	if (ray->mapY >= 0 && ray->mapX >= 0 && ray->mapY < global->map->map_height
		&& ray->mapX < global->map->map_width)
	{
		if (global->map->map[ray->mapY][ray->mapX] == '1'
			|| global->map->map[ray->mapY][ray->mapX] == '2'
			|| global->map->map[ray->mapY][ray->mapX] == '3'
			|| global->map->map[ray->mapY][ray->mapX] == '4')
		{
			ray->hit = 1;
			ray->side = -1;
		}
	}
}

void	calculate_step(t_rat *ray, t_global *global)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (global->player->pos.x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - global->player->pos.x) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (global->player->pos.y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - global->player->pos.y) * ray->deltaDistY;
	}
}

void	calculate_wall_height(t_rat *ray)
{
	if (ray->hit == 1 && ray->side == -1)
		ray->perpWallDist = 0.1;
	else
	{
		if (ray->side == 0)
			ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
		else
			ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
		if (ray->perpWallDist <= 0.1)
			ray->perpWallDist = 0.1;
	}
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
}

void	set_wall_color(t_rat *ray, t_global *global)
{
	int	r;
	int	g;
	int	b;

	if (ray->side == -1)
	{
		if (ray->rayDirX > 0 && ray->rayDirY > 0)
			ray->color = 0x808080;
		else if (ray->rayDirX > 0 && ray->rayDirY <= 0)
			ray->color = 0x707070;
		else if (ray->rayDirX <= 0 && ray->rayDirY > 0)
			ray->color = 0x909090;
		else
			ray->color = 0x606060;
	}
	else if (ray->mapY >= 0 && ray->mapX >= 0 && ray->mapY < global->map->map_height
		&& ray->mapX < global->map->map_width)
	{
		switch (global->map->map[ray->mapY][ray->mapX])
		{
			case '1': ray->color = 0xFF0000; break;
			case '2': ray->color = 0x00FF00; break;
			case '3': ray->color = 0x0000FF; break;
			case '4': ray->color = 0xFFFFFF; break;
			default: ray->color = 0xFFFF00; break;
		}
		if (ray->side == 1)
		{
			r = ((ray->color >> 16) & 0xFF) / 2;
			g = ((ray->color >> 8) & 0xFF) / 2;
			b = (ray->color & 0xFF) / 2;
			ray->color = (r << 16) | (g << 8) | b;
		}
	}
	else
		ray->color = 0x000000;
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
		if (global->map->map[ray->mapY][ray->mapX] == '1'
			|| global->map->map[ray->mapY][ray->mapX] == '2'
			|| global->map->map[ray->mapY][ray->mapX] == '3'
			|| global->map->map[ray->mapY][ray->mapX] == '4')
			ray->hit = 1;
	}
}