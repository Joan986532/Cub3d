#include "cub3d.h"

void	pov_player(t_mlx_data *data, t_player *player)
{
	t_point		point;
	
	point.x1 = player->pos.x;
	point.y1 = player->pos.y;
	point.x2 = point.x1 + player->fwd.x * 100;
	point.y2 = point.y1 + player->fwd.y * 100;
	bresenham(&point, &data->view);
}
