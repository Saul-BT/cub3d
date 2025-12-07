/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:21:41 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/25 20:21:43 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static float	player_init_angle(char c)
{
	if (c == 'N')
		return (N);
	if (c == 'S')
		return (S);
	if (c == 'E')
		return (E);
	if (c == 'W')
		return (W);
	return (ERROR);
}

void	init_player_position(t_cub *cub)
{
    int	i;
    int	j;

    j = 0;
	cub->player->x = 0;
	cub->player->y = 0;
    while (j < cub->map_height)
    {
        i = 0;
        while (cub->map[j] && cub->map[j][i])
        {
            if (is_player(cub->map[j][i]))
            {
                cub->player->x = i;
                cub->player->y = j;
                cub->player->angle = player_init_angle(cub->map[j][i]);
                return ;
            }
            i++;
        }
        j++;
    }
}

//TODO: remove printf debug lines
void	move_player(t_cub *cub, float dx, float dy)
{
    printf("Before move: x=%.2f, y=%.2f\n", cub->player->x, cub->player->y);
    cub->player->x += dx;
    cub->player->y += dy;
    printf("After move: x=%.2f, y=%.2f (dx=%.2f, dy=%.2f)\n", cub->player->x, cub->player->y, dx, dy);
    clear_screen(cub);
    draw_minimap(cub);
    //raycast(cub);
}

void	rotate_player(t_cub *cub, float rotation)
{
    cub->player->angle += rotation;
    if (cub->player->angle >= 2 * PI)
        cub->player->angle -= 2 * PI;
    if (cub->player->angle < 0)
        cub->player->angle += 2 * PI;
    clear_screen(cub);
    draw_minimap(cub);
    //raycast(cub);
}

int	ray_touches_wall(int px, int py, t_cub *cub)
{
	if (px < 0 || py < 0 || py >= cub->map_height || px >= cub->map_width ||
		cub->map[py][px] == '1')
		return (1);
	return (0);
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
    
    while (!ray_touches_wall(map_x, map_y, cub))
    {
		map_x = (int)(ray_x / TILE);
		map_y = (int)(ray_y / TILE);
        safe_put_pixel(cub->win->mmap, (int)ray_x, (int)ray_y, RED);
        ray_x += x_inc;
        ray_y += y_inc;
    }
}