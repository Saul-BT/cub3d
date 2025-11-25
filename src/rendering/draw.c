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
			mlx_put_pixel(win->mmap, x+i, y+j, color);
			i++;
		}
		j++;
	}
}

void	draw_minimap(t_cub *cub)
{
	int	i;
	int	j;

	get_map_dimensions(cub->map, cub);
	j = 0;
	while (j < cub->map_height)
	{
		i = 0;
		while (i < cub->map_width)
		{
			if (cub->map[j][i] == '1')
				draw_cube(cub->win, i*TILE, j*TILE, BLUE);
			if (is_player(cub->map[j][i]))
			{
				draw_cube(cub->win, i*TILE, j*TILE, RED);
				cub->player->x = i;
				cub->player->y = j;
			}
			i++;
		}
		j++;
	}
}


