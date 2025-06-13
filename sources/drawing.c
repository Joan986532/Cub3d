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

int	drawing(t_mlx_data *data, t_player *player)
{
	(void)player;
	t_vector2D 	vector;
	t_point		point;
	int			i;
	double		angle;

	i = 0;
	angle = 0;
	while (i < 91)
	{
		angle = i * M_PI / 180;
		point.x1 = 800;
		point.y1 = 150;
		vector.x = cosf(angle);
		vector.y = sinf(angle);
		point.x2 = point.x1 + vector.x * 1000;
		point.y2 = point.y1 + vector.y * 1000;
		bresenham(&point, &data->img);
		i++;
	}
	return (0);
}
