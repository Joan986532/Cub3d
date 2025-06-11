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

int	init_image(t_mlx_data *data)
{
	data->img.mlx_img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img.mlx_img == NULL)
	{
		free(data->img.mlx_img);
		free(data->mlx);
		free(data->win);
		return (1);
	}
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	return (0);
}

int	minimap(t_mlx_data *data, t_datamap *map)
{
	(void)map;
	int	tab[8][8] = {
		{1, 1, 1, 1, 1, 1, 1, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 1}, 
		{1, 0, 0, 0, 0, 1, 0, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 1, 0, 0, 0, 1}, 
		{1, 0, 1, 0, 0, 0, 0, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 1}, 
		{1, 1, 1, 1, 1, 1, 1, 1}, 
		};
	int	size;
	int	x;
	int	y;
	int	j;
	int	i;

	x = 0;
	y = 0;
	i = 0;
	size = 30;

	init_image(data);
	while (x < 8)
	{
		y = 0;
		while (y < 8)
		{
			if (tab[y][x] == 1)
			{
				j = 0;
				while (j < size)
				{
					i = 0;
					while (i < size)
					{
						my_pixel_put(&data->img, x * size + j, y * size + i, 99999999);
						i++;
					}
					j++;
				}
			}
			y++;
		}
		x++;
	}
	return (0);
}
