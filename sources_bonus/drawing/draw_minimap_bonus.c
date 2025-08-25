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

void	fill_minimap(char c, t_mlx_data *data, double x, double y)
{
	if (c == '0')
		my_pixel_put(&data->view, x, y, 0xFFFFFF);
	else if (c == '1')
		my_pixel_put(&data->view, x, y, 0x000000);
	else if (c == 'C' || c == 'O')
		my_pixel_put(&data->view, x, y, 0x00FF00);
	else
		my_pixel_put(&data->view, x, y, 0x0F0F0F);
}

void	get_tile(t_vector2D p, t_vector2D c, t_datamap *map, t_mlx_data *data)
{
	double	x;
	double	y;

	x = p.x / 10 + c.x;
	y = p.y / 10 + c.y;
	if (x >= 0 && x < map->map_width && y >= 0 && y < map->map_height)
		fill_minimap(map->map[(int)y][(int)x], data, p.x, p.y);
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
