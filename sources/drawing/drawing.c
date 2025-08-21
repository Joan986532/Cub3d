/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npapashv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 10:48:47 by npapashv          #+#    #+#             */
/*   Updated: 2025/08/21 10:48:49 by npapashv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_bresenham(t_point *point)
{
	point->dx = abs(point->x2 - point->x1);
	point->dy = abs(point->y2 - point->y1) * (-1);
	if (point->x1 < point->x2)
		point->sx = 1;
	else
		point->sx = -1;
	if (point->y1 < point->y2)
		point->sy = 1;
	else
		point->sy = -1;
	point->error = point->dx + point->dy;
}

void	bresenham(t_point *point, t_mlx_img *img)
{
	ft_init_bresenham(point);
	while (1)
	{
		my_pixel_put(img, point->x1, point->y1, 0xFF00FF);
		if (point->x1 == point->x2 && point->y1 == point->y2)
			break ;
		point->error2 = 2 * point->error;
		if (point->error2 >= point->dy)
		{
			if (point->x1 == point->x2)
				break ;
			point->error += point->dy;
			point->x1 += point->sx;
		}
		if (point->error2 <= point->dx)
		{
			if (point->y1 == point->y2)
				break ;
			point->error += point->dx;
			point->y1 += point->sy;
		}
	}
}
