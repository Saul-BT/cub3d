/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:46:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/12 03:40:03 by gade-oli         ###   ########.fr       */
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

void	get_map_dimensions(char **map, int *map_width, int *map_height)
{
	int	y;
	int	x;
	int	max_x;

	if (!map)
		return ;
	max_x = 0;
	x = 0;
	y = 0;
	while (map[y])
	{
		x = ft_strlen(map[y]);
		if (x > max_x)
			max_x = x;
		y++;
	}
	*map_height = y;
	*map_width = max_x;
}

static void	draw_minimap_player_ray(t_cub *cub, t_player *player)
{
    float	ray_x;
    float	ray_y;
	int		map_x;
	int		map_y;

    ray_x = player->x * TILE + TILE / 2;
    ray_y = player->y * TILE + TILE / 2;
	map_x = (int)(ray_x / TILE);
	map_y = (int)(ray_y / TILE);
    while (!ray_hits_wall(map_x, map_y, cub))
    {
		map_x = (int)(ray_x / TILE);
		map_y = (int)(ray_y / TILE);
        safe_put_pixel(cub->win->mmap, (int)ray_x, (int)ray_y, RED);
        ray_x += player->dir_x;
        ray_y += player->dir_y;
    }
}

void	draw_minimap(t_cub *cub)
{
	int	i;
	int	j;
	int	player_center_x;
	int	player_center_y;

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
	player_center_x = cub->player->x * TILE + TILE / 2;
	player_center_y = cub->player->y * TILE + TILE / 2;
	draw_minimap_player_ray(cub, cub->player);
	draw_circle(cub->win, player_center_x, player_center_y);
}