#include "cub3d.h"

int	render_frame(void *info)
{
	t_global	*global;
	t_mlx_data	*data;

	global = (t_global *)info;
	if (!global || !global->data)
		return (-1);
	data = global->data;
	if (draw_minimap(data, global, global->player->minimap_width, global->player->minimap_height) == -1)
		return (-1);
    if (draw_view(data, global) == -1)
        return (-1);
    if (draw_overlay(data, global) == -1)
        return (-1);
    // Je laisse temporairement, je te laisse check/migrer les modifs
	pov_player(global->data, global->player);
	mlx_put_image_to_window(data->mlx, data->win, data->view.mlx_img, 0, 0);
    //---------------------------------------------------------------------
    mlx_put_image_to_window(data->mlx, data->win, data->view.mlx_img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->overlay.mlx_img, 0, 0);
    mlx_put_image_to_window(data->mlx, data->win, data->minimap.mlx_img, 10, HEIGHT - 10 - global->player->minimap_height);

	return (0);
}