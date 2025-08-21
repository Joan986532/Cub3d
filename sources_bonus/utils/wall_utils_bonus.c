/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@d42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:50:14 by jnauroy           #+#    #+#             */
/*   Updated: 2025/08/21 10:50:14 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	calculate_wall_height(t_rat *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	if (ray->perp_wall_dist <= 0.1)
		ray->perp_wall_dist = 0.1;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static void	set_texture_for_hit(t_rat *ray, t_global *global,
								double *wall_x, int is_horizontal)
{
	if (is_horizontal)
	{
		if (global->map->map[ray->map_y][ray->map_x] == 'C')
			ray->texture = &global->door_texture;
		else if (ray->step_x > 0)
			ray->texture = &global->east_texture;
		else
			ray->texture = &global->west_texture;
		*wall_x = global->player->pos.y + ray->perp_wall_dist * ray->ray_dir_y;
	}
	else
	{
		if (global->map->map[ray->map_y][ray->map_x] == 'C')
			ray->texture = &global->door_texture;
		else if (ray->step_y > 0)
			ray->texture = &global->south_texture;
		else
			ray->texture = &global->north_texture;
		*wall_x = global->player->pos.x + ray->perp_wall_dist * ray->ray_dir_x;
	}
}

static void	calculate_texture_x(t_rat *ray, double wall_x)
{
	int	tex_width;

	wall_x -= floor(wall_x);
	tex_width = ray->texture->width;
	ray->tex_x = (int)(wall_x * tex_width);
	if ((ray->side == 0 && ray->ray_dir_x > 0)
		|| (ray->side == 1 && ray->ray_dir_y < 0))
		ray->tex_x = tex_width - ray->tex_x - 1;
	if (ray->tex_x < 0)
		ray->tex_x = 0;
	if (ray->tex_x >= tex_width)
		ray->tex_x = tex_width - 1;
	ray->wall_x = wall_x;
}

void	set_wall_texture(t_rat *ray, t_global *global)
{
	double	wall_x;

	if (ray->map_y >= 0 && ray->map_x >= 0
		&& ray->map_y < global->map->map_height
		&& ray->map_x < global->map->map_width)
	{
		set_texture_for_hit(ray, global, &wall_x, !ray->side);
		if (ray->texture)
			calculate_texture_x(ray, wall_x);
		ray->color = 0xFFFF00;
	}
	else
	{
		ray->color = 0x000000;
		ray->texture = NULL;
	}
}
