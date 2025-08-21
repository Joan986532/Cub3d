/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npapashv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:51:10 by npapashv          #+#    #+#             */
/*   Updated: 2025/08/21 10:51:11 by npapashv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_ray(t_rat *ray, int x, t_global *global)
{
	t_player	*player;

	player = global->player;
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = player->fwd.x + player->plane.x * ray->camera_x;
	ray->ray_dir_y = player->fwd.y + player->plane.y * ray->camera_x;
	ray->map_x = floor(player->pos.x);
	ray->map_y = floor(player->pos.y);
	if (ray->ray_dir_x != 0)
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	else
		ray->delta_dist_x = 1e30;
	if (ray->ray_dir_y != 0)
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
	else
		ray->delta_dist_y = 1e30;
	ray->hit = 0;
	ray->side = 0;
}

void	calculate_step(t_rat *ray, t_player *player)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (player->pos.x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - player->pos.x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (player->pos.y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - player->pos.y)
			* ray->delta_dist_y;
	}
}

int	is_out_of_map_bound(t_rat *ray, t_global *global, int limit)
{
	return (ray->map_x < -limit
		|| ray->map_x >= global->map->map_width + limit
		|| ray->map_y < -limit
		|| ray->map_y >= global->map->map_height + limit);
}

void	perform_dda(t_rat *ray, t_global *global)
{
	while (ray->hit == 0)
	{
		ray->side = ray->side_dist_x >= ray->side_dist_y;
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
		}
		if ((ray->side == 0 && ray->side_dist_x - ray->delta_dist_x >= 100)
			|| (ray->side == 1 && ray->side_dist_y - ray->delta_dist_y >= 100))
		{
			ray->hit = 1;
			break ;
		}
		if (is_out_of_map_bound(ray, global, 0))
			continue ;
		if (global->map->map[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}
