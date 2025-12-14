/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:46:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 14:36:24 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static int	is_wall_at(t_cub *cub, int x, int y)
{
	if (x < 0 || y < 0 || x >= cub->map.width || y >= cub->map.height
		|| cub->map.raw[y][x] == '1')
		return (1);
	return (0);
}

static void	draw_grid(t_win *win)
{
	int		x;
	int		y;
	t_point	p1;
	t_point	p2;

	x = 0;
	while (x < MMAP_SIZE)
	{
		p1 = (t_point){x, 0};
		p2 = (t_point){x, MMAP_SIZE - 1};
		draw_line(win, p1, p2, GREEN);
		x += TILE;
	}
	y = 0;
	while (y < MMAP_SIZE)
	{
		p1 = (t_point){0, y};
		p2 = (t_point){MMAP_SIZE - 1, y};
		draw_line(win, p1, p2, GREEN);
		y += TILE;
	}
}

static void	draw_player_ray(t_cub *cub, int view)
{
	double		dist;
	t_dpoint	wall;
	t_dpoint	player_tile;
	t_point		end;

	player_tile.x = (int)cub->player->pos.x + 0.5;
	player_tile.y = (int)cub->player->pos.y + 0.5;
	if (is_wall_at(cub, player_tile.x, player_tile.y))
		return ;
	dist = 0.0;
	while (dist < view)
	{
		wall.x = player_tile.x + cub->player->dir.x * dist;
		wall.y = player_tile.y + cub->player->dir.y * dist;
		if (is_wall_at(cub, (int)wall.x, (int)wall.y))
			break ;
		dist += MMAP_RAY_STEP;
	}
	end.x = view * TILE + TILE / 2 + (int)((wall.x - player_tile.x) * TILE);
	end.y = view * TILE + TILE / 2 + (int)((wall.y - player_tile.y) * TILE);
	draw_line(cub->win, (t_point){view * TILE + TILE / 2, view * TILE + TILE
		/ 2}, end, RED);
}

static void	draw_tiles(t_cub *cub, int view)
{
	t_point	i;
	t_point	map;

	i.y = 0;
	while (i.y < view * 2)
	{
		map.y = (int)cub->player->pos.y - view + i.y;
		i.x = 0;
		while (i.x < view * 2)
		{
			map.x = (int)cub->player->pos.x - view + i.x;
			if (map.x >= 0 && map.x < cub->map.width && map.y >= 0
				&& map.y < cub->map.height)
			{
				if (cub->map.raw[map.y][map.x] == '1')
					draw_cube(cub->win, i.x * TILE, i.y * TILE, BLUE);
				else
					draw_cube(cub->win, i.x * TILE, i.y * TILE, WHITE);
			}
			else
				draw_cube(cub->win, i.x * TILE, i.y * TILE, BLACK);
			i.x++;
		}
		i.y++;
	}
}

void	draw_minimap(t_cub *cub)
{
	int		view;
	t_point	player_pos;

	view = MMAP_SIZE / TILE / 2;
	player_pos.x = (MMAP_SIZE / TILE / 2) * TILE + TILE / 2;
	player_pos.y = (MMAP_SIZE / TILE / 2) * TILE + TILE / 2;
	draw_tiles(cub, view);
	draw_grid(cub->win);
	draw_player_ray(cub, view);
	draw_circle(cub->win, player_pos.x, player_pos.y);
}
