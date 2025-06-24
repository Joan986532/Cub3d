#include "cub3d_bonus.h"

void	calculate_texture_params(t_stripe *stripe,
		double *tex_pos, double *step)
{
	int	virtual_height;

	virtual_height = (int)(HEIGHT / stripe->perp_wall_dist);
	if (virtual_height > HEIGHT)
		*tex_pos = (virtual_height - HEIGHT) / 2.0 / virtual_height
			* stripe->texture->height;
	else
		*tex_pos = 0.0;
	*step = (double)stripe->texture->height / virtual_height;
}

void	set_stripe(t_stripe *stripe, t_rat *ray, int x)
{
	stripe->x = x;
	stripe->y0 = ray->draw_start;
	stripe->y1 = ray->draw_end;
	stripe->color = ray->color;
	stripe->texture = ray->texture;
	stripe->tex_x = ray->tex_x;
	stripe->wall_x = ray->wall_x;
	stripe->side = ray->side;
	stripe->perp_wall_dist = ray->perp_wall_dist;
}
