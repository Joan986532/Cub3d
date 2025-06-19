#include "cub3d.h"

void draw_stripe(int x, int y0, int y1, int color, t_mlx_data *data, t_global *global)
{
    int i;
    int start;
    int end;

    if (x < 0 || x >= WIDTH || y0 > y1)
        return;
    if (y0 < 0)
        y0 = 0;
    if (y1 >= HEIGHT)
        y1 = HEIGHT - 1;
    start = y0;
    end = y1;
    i = 0;
    while (i < HEIGHT)
    {
        if (i < start)
            my_pixel_put(&data->view, x, i, global->map->ceiling);
        else if (i <= end)
            my_pixel_put(&data->view, x, i, color);
        else
            my_pixel_put(&data->view, x, i, global->map->floor);
        i++;
    }
}

int		draw_view(t_mlx_data *data, t_global *global)
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
            
            // Check bounds to prevent segfault
            if (mapY < 0 || mapX < 0 || mapY >= global->map->map_height || mapX >= global->map->map_width)
            {
                hit = 1; // Hit boundary of map
                continue;
            }
            
            //Check if ray has hit a wall (anything that's not a floor '0')
            if (global->map->map[mapY][mapX] == '1' || 
                global->map->map[mapY][mapX] == '2' || 
                global->map->map[mapY][mapX] == '3' || 
                global->map->map[mapY][mapX] == '4')
            {
                hit = 1;
            }
        } 
        
        //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
        if(side == 0) 
            perpWallDist = (sideDistX - deltaDistX);
        else          
            perpWallDist = (sideDistY - deltaDistY);
        
        // Prevent division by zero or negative values
        if (perpWallDist <= 0.1)
            perpWallDist = 0.1;
            
        //Calculate height of line to draw on screen
        int lineHeight = (int)(HEIGHT / perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        int drawStart = -lineHeight / 2 + HEIGHT / 2;
        if(drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + HEIGHT / 2;
        if(drawEnd >= HEIGHT) drawEnd = HEIGHT - 1;
        
        //choose wall color - corrected RGB values
        int color;
        // Check bounds to prevent segfault
        if (mapY >= 0 && mapX >= 0 && mapY < global->map->map_height && mapX < global->map->map_width)
        {
            switch(global->map->map[mapY][mapX])
            {
            case '1':  color = 0xFF0000;  break; // Red (0xFF0000)
            case '2':  color = 0x00FF00;  break; // Green (0x00FF00)
            case '3':  color = 0x0000FF;  break; // Blue (0x0000FF)
            case '4':  color = 0xFFFFFF;  break; // White (0xFFFFFF)
            default: color = 0xFFFF00; break; // Yellow (0xFFFF00)
            }

            //give x and y sides different brightness
            if (side == 1) 
            {
                // Divide each RGB component separately to maintain color hue
                int r = ((color >> 16) & 0xFF) / 2;
                int g = ((color >> 8) & 0xFF) / 2;
                int b = (color & 0xFF) / 2;
                color = (r << 16) | (g << 8) | b;
            }
        }
        else
        {
            color = 0x000000; // Black for out of bounds
        }

        //draw the pixels of the stripe as a vertical line
        draw_stripe(x, drawStart, drawEnd, color, data, global);
    }
	return (0);
}
