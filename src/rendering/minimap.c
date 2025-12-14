/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:46:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 11:31:46 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	ray_hits_wall(int px, int py, t_cub *cub)
{
	if (px < 0 || py < 0 || py >= cub->map_height || px >= cub->map_width ||
		cub->map[py][px] == '1')
		return (1);
	return (0);
}

//TODO: bonus include texture loading for ceiling and floor
int	init_minimap(t_win *win)
{
	win->mmap = mlx_new_image(win->mlx, MMAP_SIZE, MMAP_SIZE);
    if (!win->mmap)
    {
        mlx_delete_image(win->mlx, win->game);
        mlx_close_window(win->mlx);
        return (ERROR);
    }
    if (mlx_image_to_window(win->mlx, win->mmap, WIN_WIDTH - MMAP_SIZE, 20) == -1)
    {
        mlx_delete_image(win->mlx, win->mmap);
        mlx_delete_image(win->mlx, win->game);
        mlx_close_window(win->mlx);
        return (ERROR);
    }
	return (SUCCESS);
}

static void	draw_grid_v(t_win *win)
{
    int		x;
    t_point	p1;
    t_point	p2;

    x = 0;
    while (x < MMAP_SIZE)
    {
        p1.x = x;
        p1.y = 0;
        p2.x = x;
        p2.y = MMAP_SIZE - 1;
        draw_line(win, p1, p2, GREEN);
        x += TILE;
    }
}

static void	draw_grid_h(t_win *win)
{
    int		y;
    t_point	p1;
    t_point	p2;

    y = 0;
    while (y < MMAP_SIZE)
    {
        p1.x = 0;
        p1.y = y;
        p2.x = MMAP_SIZE - 1;
        p2.y = y;
        draw_line(win, p1, p2, GREEN);
        y += TILE;
    }
}

void	draw_grid(t_win *win)
{
    draw_grid_v(win);
    draw_grid_h(win);
}

void	draw_minimap(t_cub *cub)
{
    int	view;
    int	row;
    int	col;
    int	map_y;
    int	map_x;

    view = MMAP_SIZE / TILE;
    row = 0;
    while (row < view)
    {
        map_y = (int)cub->player->y - view / 2 + row;
        col = 0;
        while (col < view)
        {
            map_x = (int)cub->player->x - view / 2 + col;
            if (map_x >= 0 && map_x < cub->map_width
                && map_y >= 0 && map_y < cub->map_height)
            {
                if (cub->map[map_y][map_x] == '1')
                    draw_cube(cub->win, col * TILE, row * TILE, BLUE);
                else
                    draw_cube(cub->win, col * TILE, row * TILE, WHITE);
            }
            else
                draw_cube(cub->win, col * TILE, row * TILE, BLACK);
            col++;
        }
        row++;
    }
    draw_grid(cub->win);
    draw_circle(cub->win,
        (MMAP_SIZE / TILE / 2) * TILE + TILE / 2,
        (MMAP_SIZE / TILE / 2) * TILE + TILE / 2);
}