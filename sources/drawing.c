#include "cub3d.h"

int	drawing(t_mlx_data *data, t_global *global)
{
	int		photons;
	int		x;
	int		y;

	(void)global;
	photons = 0;
	x = 826;
	y = 126;
	while (photons < 500)
	{
		my_pixel_put(&data->img, x, y, 16711680);
		x *= sin(M_PI / 6);
		y *= cos(M_PI / 6);
		photons++;
	}
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	return (0);
}
