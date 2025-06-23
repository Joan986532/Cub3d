#include "cub3d_bonus.h"

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
		my_pixel_put(img, point->x1, point->y1, 0x0000FF);
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
