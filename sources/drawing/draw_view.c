#include "cub3d.h"

static void	draw_stripe(t_stripe stripe, t_mlx_data *data, t_global *global)
{
	int	i;
    int ceiling;
    int floor;
    int tex_y;
    int color;
    int tex_height;

    ceiling = global->map->ceiling;
    floor = global->map->floor;
    if(global->player->pos.x < 0 || global->player->pos.x >= global->map->map_width
        || global->player->pos.y < 0 || global->player->pos.y >= global->map->map_height
        || global->map->map[(int)global->player->pos.y][(int)global->player->pos.x] == ' ')
    {
        ceiling = 0x000000;
        floor = 0x000000;
    }
	if (stripe.x < 0 || stripe.x >= WIDTH || stripe.y0 > stripe.y1)
		return ;
	if (stripe.y0 < 0)
		stripe.y0 = 0;
	if (stripe.y1 >= HEIGHT)
		stripe.y1 = HEIGHT - 1;

	// Vérifier si la texture est valide
	if (stripe.texture == NULL)
	{
		// Si pas de texture valide, dessiner en couleur unie
		i = 0;
		while (i < HEIGHT)
		{
			if (i < stripe.y0)
				my_pixel_put(&data->view, stripe.x, i, ceiling);
			else if (i >= stripe.y0 && i <= stripe.y1)
				my_pixel_put(&data->view, stripe.x, i, stripe.color);
			else
				my_pixel_put(&data->view, stripe.x, i, floor);
			i++;
		}
		return;
	}

	int virtual_height = (int)(HEIGHT / stripe.perpWallDist);
	
	double tex_pos = 0.0;
	if (virtual_height > HEIGHT)
		tex_pos = (virtual_height - HEIGHT) / 2.0 / virtual_height * stripe.texture->height;
	double step = (double)stripe.texture->height / virtual_height;
	
	tex_height = stripe.texture->height;

	i = 0;
	while (i < HEIGHT)
	{
		if (i < stripe.y0)
		{
			my_pixel_put(&data->view, stripe.x, i, ceiling);
		}
		else if (i >= stripe.y0 && i <= stripe.y1)
		{
			// Calculer la coordonnée y de la texture
			tex_y = (int)tex_pos & (tex_height - 1);
			tex_pos += step;
			
			// Récupérer la couleur du pixel dans la texture
			color = get_texture_color(stripe.texture, stripe.tex_x, tex_y);
			
			// Assombrir les murs selon le côté
			if (stripe.side == 1)
			{
				int r = ((color >> 16) & 0xFF) / 2;
				int g = ((color >> 8) & 0xFF) / 2;
				int b = (color & 0xFF) / 2;
				color = (r << 16) | (g << 8) | b;
			}
			
			my_pixel_put(&data->view, stripe.x, i, color);
		}
		else
		{
			my_pixel_put(&data->view, stripe.x, i, floor);
		}
		i++;
	}
}

static void set_stripe(t_stripe *stripe, t_rat *ray, int x)
{
	stripe->x = x;
	stripe->y0 = ray->drawStart;
	stripe->y1 = ray->drawEnd;
	stripe->color = ray->color;
	stripe->texture = ray->texture;
	stripe->tex_x = ray->tex_x;
	stripe->wall_x = ray->wall_x;
	stripe->side = ray->side;
	stripe->perpWallDist = ray->perpWallDist;
}

int	draw_view(t_mlx_data *data, t_global *global)
{
	t_rat		ray;
	t_stripe	stripe;
	int			x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, x, global);
		calculate_step(&ray, global);
		perform_dda(&ray, global);
		calculate_wall_height(&ray);
		set_wall_color(&ray, global);		
		set_stripe(&stripe, &ray, x);
		draw_stripe(stripe, data, global);
		x++;
	}
	return (0);
}
