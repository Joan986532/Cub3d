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
    t_rat ray;
    
    for(int x = 0; x < WIDTH; x++)
    {
        //calculate ray position and direction
        ray.cameraX = 2 * x / (double)WIDTH - 1; //x-coordinate in camera space
        ray.rayDirX = global->player->fwd.x + global->player->plane.x * ray.cameraX;
        ray.rayDirY = global->player->fwd.y + global->player->plane.y * ray.cameraX;
        
        //which box of the map we're in
        ray.mapX = (int)global->player->pos.x;
        ray.mapY = (int)global->player->pos.y;

        //length of ray from one x or y-side to next x or y-side
        ray.deltaDistX = (ray.rayDirX == 0) ? 1e30 : fabs(1 / ray.rayDirX);
        ray.deltaDistY = (ray.rayDirY == 0) ? 1e30 : fabs(1 / ray.rayDirY);

        ray.hit = 0; //was there a wall hit?
        
        //calculate step and initial sideDist
        if (ray.rayDirX < 0)
        {
            ray.stepX = -1;
            ray.sideDistX = (global->player->pos.x - ray.mapX) * ray.deltaDistX;
        }
        else
        {
            ray.stepX = 1;
            ray.sideDistX = (ray.mapX + 1.0 - global->player->pos.x) * ray.deltaDistX;
        }
        if (ray.rayDirY < 0)
        {
            ray.stepY = -1;
            ray.sideDistY = (global->player->pos.y - ray.mapY) * ray.deltaDistY;
        }
        else
        {
            ray.stepY = 1;
            ray.sideDistY = (ray.mapY + 1.0 - global->player->pos.y) * ray.deltaDistY;
        }
        
        //perform DDA
        while (ray.hit == 0)
        {
            //jump to next map square, either in x-direction, or in y-direction
            if (ray.sideDistX < ray.sideDistY)
            {
                ray.sideDistX += ray.deltaDistX;
                ray.mapX += ray.stepX;
                ray.side = 0;
            }
            else
            {
                ray.sideDistY += ray.deltaDistY;
                ray.mapY += ray.stepY;
                ray.side = 1;
            }
            
            // Check bounds to prevent segfault
            if (ray.mapY < 0 || ray.mapX < 0 || ray.mapY >= global->map->map_height || ray.mapX >= global->map->map_width)
            {
                ray.hit = 1; // Hit boundary of map
                continue;
            }
            
            //Check if ray has hit a wall (anything that's not a floor '0')
            if (global->map->map[ray.mapY][ray.mapX] == '1' || 
                global->map->map[ray.mapY][ray.mapX] == '2' || 
                global->map->map[ray.mapY][ray.mapX] == '3' || 
                global->map->map[ray.mapY][ray.mapX] == '4')
            {
                ray.hit = 1;
            }
        } 
        
        //Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
        if(ray.side == 0) 
            ray.perpWallDist = (ray.sideDistX - ray.deltaDistX);
        else          
            ray.perpWallDist = (ray.sideDistY - ray.deltaDistY);
        
        // Prevent division by zero or negative values
        if (ray.perpWallDist <= 0.1)
            ray.perpWallDist = 0.1;
            
        //Calculate height of line to draw on screen
        ray.lineHeight = (int)(HEIGHT / ray.perpWallDist);

        //calculate lowest and highest pixel to fill in current stripe
        ray.drawStart = -ray.lineHeight / 2 + HEIGHT / 2;
        if(ray.drawStart < 0) ray.drawStart = 0;
        ray.drawEnd = ray.lineHeight / 2 + HEIGHT / 2;
        if(ray.drawEnd >= HEIGHT) ray.drawEnd = HEIGHT - 1;
        
        //choose wall color - corrected RGB values
        // Check bounds to prevent segfault
        if (ray.mapY >= 0 && ray.mapX >= 0 && ray.mapY < global->map->map_height && ray.mapX < global->map->map_width)
        {
            switch(global->map->map[ray.mapY][ray.mapX])
            {
            case '1':  ray.color = 0xFF0000;  break; // Red (0xFF0000)
            case '2':  ray.color = 0x00FF00;  break; // Green (0x00FF00)
            case '3':  ray.color = 0x0000FF;  break; // Blue (0x0000FF)
            case '4':  ray.color = 0xFFFFFF;  break; // White (0xFFFFFF)
            default: ray.color = 0xFFFF00; break; // Yellow (0xFFFF00)
            }

            //give x and y sides different brightness
            if (ray.side == 1) 
            {
                // Divide each RGB component separately to maintain color hue
                int r = ((ray.color >> 16) & 0xFF) / 2;
                int g = ((ray.color >> 8) & 0xFF) / 2;
                int b = (ray.color & 0xFF) / 2;
                ray.color = (r << 16) | (g << 8) | b;
            }
        }
        else
        {
            ray.color = 0x000000; // Black for out of bounds
        }

        //draw the pixels of the stripe as a vertical line
        draw_stripe(x, ray.drawStart, ray.drawEnd, ray.color, data, global);
    }
	return (0);
}
