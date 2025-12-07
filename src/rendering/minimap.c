/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:46:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/24 20:46:39 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//atm for 2D minimap
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

void	draw_minimap_player_ray(t_cub *cub, t_player *player)
{
    float	ray_x;
    float	ray_y;
    float	x_inc;
    float	y_inc;
	int		map_x;
	int		map_y;

    ray_x = player->x * TILE + TILE / 2;
    ray_y = player->y * TILE + TILE / 2;
    
    x_inc = cos(player->angle);
    y_inc = sin(player->angle);

	map_x = (int)(ray_x / TILE);
	map_y = (int)(ray_y / TILE);
    
    while (!ray_hits_wall(map_x, map_y, cub))
    {
		map_x = (int)(ray_x / TILE);
		map_y = (int)(ray_y / TILE);
        safe_put_pixel(cub->win->mmap, (int)ray_x, (int)ray_y, RED);
        ray_x += x_inc;
        ray_y += y_inc;
    }
}