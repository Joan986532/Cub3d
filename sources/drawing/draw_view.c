#include "cub3d.h"

static void	draw_untextured_stripe(t_stripe stripe, t_mlx_data *data,
							int ceiling, int floor)
{
	int	i;

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
}

static void	draw_textured_stripe(t_stripe stripe, t_mlx_data *data,
							int ceiling, int floor)
{
	int		i;
	int		tex_y;
	int		color;
	int		tex_height;
	double	tex_pos;
	double	step;

	calculate_texture_params(&stripe, &tex_pos, &step);
	tex_height = stripe.texture->height;
	i = 0;
	while (i < HEIGHT)
	{
		if (i < stripe.y0)
			my_pixel_put(&data->view, stripe.x, i, ceiling);
		else if (i >= stripe.y0 && i <= stripe.y1)
		{
			tex_y = (int)tex_pos & (tex_height - 1);
			tex_pos += step;
			color = get_texture_color(stripe.texture, stripe.tex_x, tex_y);
			color = get_shaded_color(color, stripe.side);
			my_pixel_put(&data->view, stripe.x, i, color);
		}
		else
			my_pixel_put(&data->view, stripe.x, i, floor);
		i++;
	}
}

static void	draw_stripe(t_stripe stripe, t_mlx_data *data, t_global *global)
{
	int	ceiling;
	int	floor;

	set_ceiling_floor_colors(global, &ceiling, &floor);
	if (stripe.x < 0 || stripe.x >= WIDTH || stripe.y0 > stripe.y1)
		return ;
	if (stripe.y0 < 0)
		stripe.y0 = 0;
	if (stripe.y1 >= HEIGHT)
		stripe.y1 = HEIGHT - 1;

	if (stripe.texture == NULL)
		draw_untextured_stripe(stripe, data, ceiling, floor);
	else
		draw_textured_stripe(stripe, data, ceiling, floor);
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
