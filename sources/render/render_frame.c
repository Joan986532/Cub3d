#include "cub3d.h"

int	render_frame(void *info)
{
	t_global	*global;
	t_mlx_data	*data;

	global = (t_global *)info;
	data = global->data;
	draw_view(data, global);
	choose_direction(global->player);
	mlx_put_image_to_window(data->mlx, data->win, data->view.mlx_img, 0, 0);
	return (0);
}
