#include "cub3d.h"

static void	draw_stripe(t_stripe stripe, t_mlx_data *data, t_global *global)
{
	int	i;
    int ceiling;
    int floor;

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
