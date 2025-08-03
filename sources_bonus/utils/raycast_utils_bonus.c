#include "cub3d_bonus.h"

void	init_ray(t_rat *ray, int x, t_global *global)
{
	t_player	*player;

	player = global->player;
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->ray_dir_x = player->fwd.x + player->plane.x * ray->camera_x;
	ray->ray_dir_y = player->fwd.y + player->plane.y * ray->camera_x;
	ray->map_x = (int)player->pos.x;
	ray->map_y = (int)player->pos.y;
	ray->door_hit = 0;
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

static void	check_door(t_rat *ray, t_global *global)
{
	double	dist;

	if (global->map->map[ray->map_y][ray->map_x] == 'C'
		|| global->map->map[ray->map_y][ray->map_x] == 'O')
	{
		if (ray->side == 0)
			dist = (ray->side_dist_x - ray->delta_dist_x);
		else
			dist = (ray->side_dist_y - ray->delta_dist_y);
		if (dist <= 2)
		{
			ray->door_hit_location[0] = ray->map_x;
			ray->door_hit_location[1] = ray->map_y;
			ray->door_hit = 1;
		}
	}
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
		if (is_out_of_map_bound(ray, global, 100))
		{
			ray->hit = 1;
			break ;
		}
		if (is_out_of_map_bound(ray, global, 0))
			continue ;
		if (global->map->map[ray->map_y][ray->map_x] == '1'
			|| global->map->map[ray->map_y][ray->map_x] == 'C')
			ray->hit = 1;
		check_door(ray, global);
	}
}
