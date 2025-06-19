#include "cub3d.h"

// MAP: global->map->map
// PLAYER POS: global->player->pos
// PLAYER FWD: global->player->fwd
// CAMERA PLANE: global->player->plane
// SCREEN WIDHT: WIDTH
// SCREEN HEIGHT: HEIGHT

void verLine(int x, int y0, int y1, int color, t_mlx_data *data)
{
    for(int y = y0; y <= y1; y++)
    {
        my_pixel_put(&data->view, x, y, color);
    }
}

int		draw_overlay(t_mlx_data *data, t_global *global)
{
    for(int x = 0; x < WIDTH; x++)
    {
        //calculate ray position and direction
        double cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
        double rayDirX = global->player->fwd.x + global->player->plane.x * cameraX;
        double rayDirY = global->player->fwd.y + global->player->plane.y * cameraX;
        //which box of the map we're in
        int mapX = (int)global->player->pos.x;
        int mapY = (int)global->player->pos.y;

        //length of ray from current position to next x or y-side
        double sideDistX;
        double sideDistY;

        //length of ray from one x or y-side to next x or y-side
        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;

        //what direction to step in x or y-direction (either +1 or -1)
        int stepX;
        int stepY;

        int hit = 0; //was there a wall hit?
        int side; //was a NS or a EW wall hit?
        //calculate step and initial sideDist
        if (rayDirX < 0)
        {
            stepX = -1;
            sideDistX = (global->player->pos.x - mapX) * deltaDistX;
        }
        else
        {
            stepX = 1;
            sideDistX = (mapX + 1.0 - global->player->pos.x) * deltaDistX;
        }
        if (rayDirY < 0)
        {
            stepY = -1;
            sideDistY = (global->player->pos.y - mapY) * deltaDistY;
        }
        else
        {
            stepY = 1;
            sideDistY = (mapY + 1.0 - global->player->pos.y) * deltaDistY;
        }
              //perform DDA
        while (hit == 0)
        {
            //jump to next map square, either in x-direction, or in y-direction
            if (sideDistX < sideDistY)
            {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            }
            else
            {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            //Check if ray has hit a wall
            if (global->map->map[mapY][mapX] != '0') hit = 1;
        } 
        //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
        if(side == 0) perpWallDist = (sideDistX - deltaDistX);
        else          perpWallDist = (sideDistY - deltaDistY);
        //Calculate height of line to draw on screen
        int lineHeight = (int)(HEIGHT / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if(drawStart < 0)drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;
        //choose wall color
        int color;
        switch(global->map->map[mapY][mapX])
        {
        case '1':  color = 0x00FF00;  break; //red
        case '2':  color = 0x0000FF;  break; //green
        case '3':  color = 0xFF0000;   break; //blue
        case '4':  color = 0xFFFFFF;  break; //white
        default: color = 0xFFFF00; break; //yellow
        }

        //give x and y sides different brightness
        if (side == 1) {color = color / 2;}

        //draw the pixels of the stripe as a vertical line
        verLine(x, drawStart, drawEnd, color, data);
    }
	return (0);
}
