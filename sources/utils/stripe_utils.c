#include "cub3d.h"

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

int	get_shaded_color(int color, int side)
{
	int	r;
	int	g;
	int	b;

	if (side == 1)
	{
		r = ((color >> 16) & 0xFF) / 2;
		g = ((color >> 8) & 0xFF) / 2;
		b = (color & 0xFF) / 2;
		color = (r << 16) | (g << 8) | b;
	}
	return (color);
}

void	set_ceiling_floor_colors(t_global *global, int *ceiling, int *floor)
{
	int	posx;
	int	posy;

	posx = (int)global->player->pos.x;
	posy = (int)global->player->pos.y;
	*ceiling = global->map->ceiling;
	*floor = global->map->floor;
	if (posx < 0 || posx >= global->map->map_width
		|| posy < 0 || posy >= global->map->map_height
		|| global->map->map[posy][posx] == ' ')
	{
		*ceiling = 0x000000;
		*floor = 0x000000;
	}
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
