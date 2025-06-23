#include "cub3d.h"

int	render_frame(void *info)
{
	t_global	*global;
	t_mlx_data	*data;

	global = (t_global *)info;
	if (!global || !global->data)
		return (-1);
	data = global->data;
	if (draw_view(data, global) == -1)
		return (-1);
	choose_direction(global->player);
	mlx_put_image_to_window(data->mlx, data->win, data->view.mlx_img, 0, 0);
	return (0);
}
