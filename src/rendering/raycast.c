/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:42:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/30 20:42:06 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/cub3d.h"

// Check if ray hit a wall or is out of bounds
int	ray_hits_wall(int px, int py, t_cub *cub)
{
	if (px < 0 || py < 0 || py >= cub->map_height || px >= cub->map_width ||
		cub->map[py][px] == '1')
		return (1);
	return (0);
}

static float	cast_ray(t_cub *cub, float ray_angle)
{
    float	ray_x;
    float	ray_y;
    float	x_step;
    float	y_step;

    // Start from player center
    ray_x = cub->player->x + 0.5;
    ray_y = cub->player->y + 0.5;
    
    x_step = cos(ray_angle) * 0.01;
    y_step = sin(ray_angle) * 0.01;
    
    while (!ray_hits_wall((int)ray_x, (int)ray_y, cub))
    {
        ray_x += x_step;
        ray_y += y_step;
    }
    
    return (sqrt(pow(ray_x - (cub->player->x + 0.5), 2) 
        + pow(ray_y - (cub->player->y + 0.5), 2)));
}

// one vertical slice of wall
static void	draw_slice(t_cub *cub, int x, float distance, float ray_angle)
{
    int		wall_height;
    int		draw_start;
    int		draw_end;
    int		y;
    float	corrected_dist;

    // fix fisheye effect
    corrected_dist = distance * cos(ray_angle - cub->player->angle);
    
    wall_height = (int)(WIN_HEIGHT / corrected_dist);
    draw_start = (WIN_HEIGHT - wall_height) / 2;
    draw_end = draw_start + wall_height;
    
    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= WIN_HEIGHT)
        draw_end = WIN_HEIGHT - 1;
    
    y = -1;
    while (++y < draw_start)
        safe_put_pixel(cub->win->mmap, x, y, CYAN);
    while (y < draw_end)
        safe_put_pixel(cub->win->mmap, x, y++, BLUE);
    while (y < WIN_HEIGHT)
        safe_put_pixel(cub->win->mmap, x, y++, GREEN);
}

void	raycast(t_cub *cub)
{
    int		x;
    float	ray_angle;
    float	angle_step;
    float	distance;

    angle_step = FOV / WIN_WIDTH;
    ray_angle = cub->player->angle - (FOV / 2);
    
    x = 0;
    while (x < WIN_WIDTH)
    {
        distance = cast_ray(cub, ray_angle);
        draw_slice(cub, x, distance, ray_angle);
        ray_angle += angle_step;
        x++;
    }
}