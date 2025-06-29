#include "cub3d.h"

void	my_pixel_put(t_mlx_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < WIDTH && x >= 0 && y < HEIGHT && y >= 0)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	init_image(t_mlx_img *img, void *mlx)
{
	img->mlx_img = mlx_new_image(mlx, 1920, 1080);
	if (img->mlx_img == NULL)
	{
		return (img_error(IMAGE, img));
	}
	img->addr = mlx_get_data_addr(img->mlx_img,
			&img->bpp, &img->line_len, &img->endian);
	return (0);
}
