/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnauroy <marvin@d42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:48:05 by jnauroy           #+#    #+#             */
/*   Updated: 2025/08/21 10:48:05 by jnauroy          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	fill_minimap(char **map, t_mlx_data *data, double x, double y)
{
	if (map[(int)y][(int)x] == '0')
		my_pixel_put(&data->minimap, x * 10, y * 10, 0xFFFFFF);
	else if (map[(int)y][(int)x] == '1')
		my_pixel_put(&data->minimap, x * 10, y * 10, 0x000000);
	else if (map[(int)y][(int)x] == 'C' || map[(int)y][(int)x] == 'O')
		my_pixel_put(&data->minimap, x * 10, y * 10, 0x00FF00);
	else
		my_pixel_put(&data->minimap, x * 10, y * 10, 0x0F0F0F);
}

int	init_minimap(t_global *global, t_mlx_data *data, t_datamap *map)
{
	double	x;
	double	y;
	int		size;

	y = 0;
	size = ft_strlen(map->map[(int)y]);
	if (init_image(&data->minimap, data->mlx,
			map->map_width * 10, map->map_height * 10) == -1)
	{
		free_textures(global);
		clear_textures(map);
		return (1);
	}
	while (map->map[(int)y])
	{
		x = 0;
		while (x < size)
		{
			fill_minimap(map->map, data, x, y);
			x += 0.1f;
		}
		y += 0.1f;
	}
	return (0);
}

int	get_minimap_color(t_mlx_img *img, int x, int y)
{
	char	*dst;
	int		color;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	color = *(unsigned int *)dst;
	return (color);
}

void	get_tile(t_vector2D p, t_vector2D c, t_datamap *map, t_mlx_data *data)
{
	double	x;
	double	y;
	int		color;

	x = p.x / 10 + c.x;
	y = p.y / 10 + c.y;
	if (x >= 0 && x < map->map_width && y >= 0 && y < map->map_height)
	{
		color = get_minimap_color(&data->minimap, x * 10, y * 10);
		my_pixel_put(&data->view, p.x, p.y, color);
	}
	else
		my_pixel_put(&data->view, p.x, p.y, map->floor);
}

int	draw_minimap(t_datamap *map, t_player *player, t_mlx_data *data)
{
	t_vector2D	point;
	t_vector2D	corner;

	point.x = 0;
	point.y = 0;
	corner.x = player->pos.x - 10;
	corner.y = player->pos.y - 10;
	while (point.y < 200)
	{
		point.x = 0;
		while (point.x < 200)
		{
			get_tile(point, corner, map, data);
			point.x++;
		}
		point.y++;
	}
	return (0);
}
