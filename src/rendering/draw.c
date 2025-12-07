/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 19:41:42 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/25 19:41:45 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

// the size of a cube is atm determined through the TILE size on defines.h
void	draw_cube(t_win *win, int x, int y, int color)
{
	int	i;
	int	j;

	j = 0;
	while (j < TILE)
	{
		i = 0;
		while (i < TILE)
		{
			safe_put_pixel(win->mmap, x+i, y+j, color);
			i++;
		}
		j++;
	}
}

void	draw_grid(t_cub *cub, t_win *win)
{
	int	x;
	int	y;

	// vertical lines
	x = 0;
	while (x <= cub->map_width * TILE)
	{
		y = 0;
		while (y < cub->map_height * TILE)
		{
			safe_put_pixel(win->mmap, x, y, GREEN);
			y++;
		}
		x += TILE;
	}
	// horizontal lines
	y = 0;
    while (y <= cub->map_height * TILE)
    {
        x = 0;
        while (x < cub->map_width * TILE)
        {
            safe_put_pixel(win->mmap, x, y, GREEN);
            x++;
        }
        y += TILE;
    }
}

void	draw_circle(t_win *win, int center_x, int center_y)
{
	int	radius;
	int	x;
	int	y;
	int	dx;
	int	dy;

	radius = TILE / 4;
	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			dx = x - center_x;
			dy = y - center_y;
			if (dx * dx + dy * dy <= radius * radius)
				safe_put_pixel(win->mmap, x, y, RED);
			x++;
		}
		y++;
	}
}
