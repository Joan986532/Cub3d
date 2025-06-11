#include "cub3d.h"

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
	int	tab[8][8] = {
		{1, 1, 1, 1, 1, 1, 1, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 1}, 
		{1, 0, 1, 0, 1, 0, 0, 1}, 
		{1, 0, 0, 1, 1, 1, 1, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 1}, 
		{1, 0, 0, 0, 0, 0, 0, 1}, 
		{1, 1, 1, 1, 1, 1, 1, 1}, 
		};
	int	tile;

	tile = 20;

	init_image(data);
	
	return (0);
}
