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

void    reset_interactive_cell(t_global *global)
{
    global->player->interactive_cell[0] = -1;
    global->player->interactive_cell[1] = -1;
}

void	update_interactive_cell(t_rat *ray, t_global *global)
{
    int x;
    int y;

    x = ray->door_hit_location[0];
    y = ray->door_hit_location[1];
    if (!ray->door_hit)
        return ;
    if (x < 0 || x >= global->map->map_width
        || y < 0 || y >= global->map->map_height)
        return ;
    if (global->map->map[y][x] == 'O' || global->map->map[y][x] == 'C')
    {
        //printf("DOOR FIND\n");
        global->player->interactive_cell[0] = x;
        global->player->interactive_cell[1] = y;
    }
    //else
        //printf("------NOT FOUND--------\n");
}