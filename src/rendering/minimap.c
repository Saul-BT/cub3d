/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:46:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 22:23:36 by sblanco-         ###   ########.fr       */
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

static void	draw_tiles(t_cub *cub, int view)
{
	t_point	i;
	t_point	map;

	i.y = 0;
	while (i.y < view * 2)
	{
		map.y = (int)cub->player.pos.y - view + i.y;
		i.x = 0;
		while (i.x < view * 2)
		{
			map.x = (int)cub->player.pos.x - view + i.x;
			if (map.x >= 0 && map.x < cub->map.width && map.y >= 0
				&& map.y < cub->map.height)
			{
				if (cub->map.raw[map.y][map.x] == '1')
					draw_cube(&cub->win, i.x * TILE, i.y * TILE, BLUE);
				else
					draw_cube(&cub->win, i.x * TILE, i.y * TILE, WHITE);
			}
			else
				draw_cube(&cub->win, i.x * TILE, i.y * TILE, BLACK);
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
	draw_circle(&cub->win, player_pos.x, player_pos.y);
}
