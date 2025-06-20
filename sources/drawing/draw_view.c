#include "cub3d.h"

static void	draw_stripe(t_stripe stripe, t_mlx_data *data, t_global *global)
{
	int	i;
	int	start;
	int	end;

	if (stripe.x < 0 || stripe.x >= WIDTH || stripe.y0 > stripe.y1)
		return ;
	if (stripe.y0 < 0)
		stripe.y0 = 0;
	if (stripe.y1 >= HEIGHT)
		stripe.y1 = HEIGHT - 1;
	start = stripe.y0;
	end = stripe.y1;
	i = 0;
	while (i < HEIGHT)
	{
		if (i < start)
			my_pixel_put(&data->view, stripe.x, i, global->map->ceiling);
		else if (i <= end)
			my_pixel_put(&data->view, stripe.x, i, stripe.color);
		else
			my_pixel_put(&data->view, stripe.x, i, global->map->floor);
		i++;
	}
}

int	draw_view(t_mlx_data *data, t_global *global)
{
	t_rat	ray;
	t_stripe	stripe;
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, x, global);
		calculate_step(&ray, global);
		perform_dda(&ray, global);
		calculate_wall_height(&ray);
		set_wall_color(&ray, global);
		
		stripe.x = x;
		stripe.y0 = ray.drawStart;
		stripe.y1 = ray.drawEnd;
		stripe.color = ray.color;
		draw_stripe(stripe, data, global);
		x++;
	}
	return (0);
}
