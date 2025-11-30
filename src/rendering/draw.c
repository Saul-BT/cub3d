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

void	clear_screen(t_cub *cub)
{
    int	x;
    int	y;

    y = 0;
    while (y < (int)cub->win->mmap->height)
    {
        x = 0;
        while (x < (int)cub->win->mmap->width)
        {
            mlx_put_pixel(cub->win->mmap, x, y, BLACK);
            x++;
        }
        y++;
    }
}

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
			mlx_put_pixel(win->mmap, x+i, y+j, color);
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
            if (x < (int)win->mmap->width && y < (int)win->mmap->height)
				mlx_put_pixel(win->mmap, x, y, GREEN);
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
            if (x < (int)win->mmap->width && y < (int)win->mmap->height)
                mlx_put_pixel(win->mmap, x, y, GREEN);
            x++;
        }
        y += TILE;
    }
}

// TODO: refactor for norminette
void	draw_player_circle(t_win *win, t_player *player)
{
	int center_x = player->x * TILE + TILE / 2;
    int center_y = player->y * TILE + TILE / 2;
	int	radius = TILE / 4;
	int	x, y;
	int	dx, dy;

	y = center_y - radius;
	while (y <= center_y + radius)
	{
		x = center_x - radius;
		while (x <= center_x + radius)
		{
			dx = x - center_x;
			dy = y - center_y;
			if (dx * dx + dy * dy <= radius * radius)
			{
                if (x >= 0 && x < (int)win->mmap->width && y >= 0 && y < (int)win->mmap->height)
					mlx_put_pixel(win->mmap, x, y, RED);
			}
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_cub *cub)
{
	int	i;
	int	j;

	get_map_dimensions(cub->map, cub);
	clear_screen(cub);
	j = 0;
	while (j < cub->map_height)
	{
		i = 0;
		while (i < cub->map_width)
		{
			if (cub->map[j][i] == '1')
				draw_cube(cub->win, i*TILE, j*TILE, BLUE);
			if (cub->map[j][i] == '0' || is_player(cub->map[j][i]))
                    draw_cube(cub->win, i*TILE, j*TILE, WHITE);
			i++;
		}
		j++;
	}
	draw_grid(cub, cub->win);
	draw_player_circle(cub->win, cub->player);
}


