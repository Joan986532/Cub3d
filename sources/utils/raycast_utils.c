#include "cub3d.h"
#include <math.h>

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
		if (global->map->map[ray->mapY][ray->mapX] == '1')
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
	double	wall_x;

	// Vérifier si les textures sont chargées
	if (global->north_texture == NULL || global->south_texture == NULL ||
		global->east_texture == NULL || global->west_texture == NULL)
	{
		ray->color = 0xFF0000; // Rouge en cas d'erreur de texture
		ray->texture = NULL;
		return;
	}

	if (ray->side == -1)
	{
		ray->color = 0x808080;
		ray->texture = global->north_texture;
		ray->tex_x = 0;
		return;
	}
	else if (ray->mapY >= 0 && ray->mapX >= 0 && ray->mapY < global->map->map_height
		&& ray->mapX < global->map->map_width)
	{
		if (ray->side == 0)
		{
			if (ray->stepX > 0)
				ray->texture = global->east_texture;
			else
				ray->texture = global->west_texture;
			
			wall_x = global->player->pos.y + ray->perpWallDist * ray->rayDirY;
		}
		else
		{
			if (ray->stepY > 0)
				ray->texture = global->south_texture;
			else
				ray->texture = global->north_texture;
			
			wall_x = global->player->pos.x + ray->perpWallDist * ray->rayDirX;
		}
		
		// Protection contre les valeurs NaN ou inf
		if (isnan(wall_x) || isinf(wall_x))
		{
			ray->color = 0x000000;
			ray->texture = NULL;
			return;
		}
		
		wall_x -= floor(wall_x);
		
		// Vérifier à nouveau que la texture est valide
		if (ray->texture == NULL)
		{
			ray->color = 0x000000;
			return;
		}
		
		int tex_width = ray->texture->width;
		ray->tex_x = (int)(wall_x * tex_width);
		if ((ray->side == 0 && ray->rayDirX > 0) || (ray->side == 1 && ray->rayDirY < 0))
			ray->tex_x = tex_width - ray->tex_x - 1;
		if (ray->tex_x < 0)
			ray->tex_x = 0;
		if (ray->tex_x >= tex_width)
			ray->tex_x = tex_width - 1;
		ray->color = 0xFFFF00;
		ray->wall_x = wall_x;
	}
	else
	{
		ray->color = 0x000000;
		ray->texture = NULL;
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