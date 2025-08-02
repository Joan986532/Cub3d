#include "cub3d_bonus.h"

void	handle_door_interact(t_global *global)
{
    t_player    *player;
    int         x;
    int         y;

    player = global->player;
    x = player->interactive_cell[0];
    y = player->interactive_cell[1];
    if (x < 0 || x >= global->map->map_width
        || y < 0 || y >= global->map->map_height)
        return ;
    if (global->map->map[y][x] == 'O')
        global->map->map[y][x] = 'C';
    else if (global->map->map[y][x] == 'C')
        global->map->map[y][x] = 'O';
}