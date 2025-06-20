#include "cub3d.h"

void	calculate_wall_height(t_rat *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = (ray->sideDistX - ray->deltaDistX);
	else
		ray->perpWallDist = (ray->sideDistY - ray->deltaDistY);
	if (ray->perpWallDist <= 0.1)
		ray->perpWallDist = 0.1;
	ray->lineHeight = (int)(HEIGHT / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + HEIGHT / 2;
	if (ray->drawEnd >= HEIGHT)
		ray->drawEnd = HEIGHT - 1;
}

static void	set_texture_for_hit(t_rat *ray, t_global *global,
								double *wall_x, int is_horizontal)
{
	if (is_horizontal)
	{
		if (ray->stepX > 0)
			ray->texture = global->east_texture;
		else
			ray->texture = global->west_texture;
		*wall_x = global->player->pos.y + ray->perpWallDist * ray->rayDirY;
	}
	else
	{
		if (ray->stepY > 0)
			ray->texture = global->south_texture;
		else
			ray->texture = global->north_texture;
		*wall_x = global->player->pos.x + ray->perpWallDist * ray->rayDirX;
	}
}

static void	calculate_texture_x(t_rat *ray, double wall_x)
{
	int	tex_width;

	wall_x -= floor(wall_x);
	tex_width = ray->texture->width;
	ray->tex_x = (int)(wall_x * tex_width);
	if ((ray->side == 0 && ray->rayDirX > 0)
		|| (ray->side == 1 && ray->rayDirY < 0))
		ray->tex_x = tex_width - ray->tex_x - 1;
	if (ray->tex_x < 0)
		ray->tex_x = 0;
	if (ray->tex_x >= tex_width)
		ray->tex_x = tex_width - 1;
	ray->wall_x = wall_x;
}

void	set_wall_color(t_rat *ray, t_global *global)
{
	double	wall_x;

	if (ray->mapY >= 0 && ray->mapX >= 0 && ray->mapY < global->map->map_height
		&& ray->mapX < global->map->map_width)
	{
		set_texture_for_hit(ray, global, &wall_x, !ray->side);
		calculate_texture_x(ray, wall_x);
		ray->color = 0xFFFF00;
	}
	else
	{
		ray->color = 0x000000;
		ray->texture = NULL;
	}
}
