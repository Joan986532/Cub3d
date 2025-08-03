#include "cub3d_bonus.h"

static void	draw_wall_pixel(t_mlx_data *data, t_stripe *s, int y, double *pos)
{
	int	tex_y;
	int	color;

	tex_y = (int)*pos & (s->texture->height - 1);
	color = get_texture_color(s->texture, s->tex_x, tex_y);
	my_pixel_put(&data->view, s->x, y, color);
	my_pixel_put(&data->view, s->x + 1, y, color);
}

static void	draw_untextured_stripe(t_stripe stripe, t_mlx_data *data,
							int ceiling, int floor)
{
	int	i;

	i = 0;
	while (i < HEIGHT)
	{
		if (i < stripe.y0)
		{
			my_pixel_put(&data->view, stripe.x, i, ceiling);
			my_pixel_put(&data->view, stripe.x + 1, i, ceiling);
		}
		else if (i >= stripe.y0 && i <= stripe.y1)
		{
			my_pixel_put(&data->view, stripe.x, i, stripe.color);
			my_pixel_put(&data->view, stripe.x + 1, i, stripe.color);
		}
		else
		{
			my_pixel_put(&data->view, stripe.x, i, floor);
			my_pixel_put(&data->view, stripe.x, i + 1, floor);
		}
		i++;
	}
}

static void	draw_textured_stripe(t_stripe stripe, t_mlx_data *data,
	int ceiling, int floor)
{
	int		y;
	double	tex_pos;
	double	step;

	calculate_texture_params(&stripe, &tex_pos, &step);
	y = 0;
	while (y < HEIGHT)
	{
		if (y < stripe.y0)
		{
			my_pixel_put(&data->view, stripe.x, y, ceiling);
			my_pixel_put(&data->view, stripe.x + 1, y, ceiling);
		}
		else if (y >= stripe.y0 && y <= stripe.y1)
		{
			draw_wall_pixel(data, &stripe, y, &tex_pos);
			tex_pos += step;
		}
		else
		{
			my_pixel_put(&data->view, stripe.x, y, floor);
			my_pixel_put(&data->view, stripe.x + 1, y, floor);
		}
		y++;
	}
}

static void	draw_stripe(t_stripe stripe, t_mlx_data *data, t_global *global)
{	
	int	ceiling;
	int	floor;

	ceiling = global->map->ceiling;
	floor = global->map->floor;
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
	int			foi;

	reset_interactive_cell(global);
	foi = 15;
	x = 0;
	while (x < WIDTH)
	{
		init_ray(&ray, x, global);
		calculate_step(&ray, global->player);
		perform_dda(&ray, global);
		if (x > WIDTH / 2 - 30 && x < WIDTH / 2 + 30)
			update_interactive_cell(&ray, global);
		calculate_wall_height(&ray);
		set_wall_texture(&ray, global);
		set_stripe(&stripe, &ray, x);
		draw_stripe(stripe, data, global);
		x += 2;
	}
	return (0);
}
