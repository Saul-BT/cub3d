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
}

void	minimap_player_ray(t_win *win, t_player *player)
{
	float	end_x;
    float	end_y;
    float	ray_x;
    float	ray_y;
    float	steps;
    float	x_inc;
    float	y_inc;
    int		i;

    end_x = (player->x * TILE + TILE / 2) + cos(player->angle) * RAY_LENGTH * TILE;
    end_y = (player->y * TILE + TILE / 2) + sin(player->angle) * RAY_LENGTH * TILE;
    
    ray_x = player->x * TILE + TILE / 2;
    ray_y = player->y * TILE + TILE / 2;
    
    steps = fmax(fabs(end_x - ray_x), fabs(end_y - ray_y));
    x_inc = (end_x - ray_x) / steps;
    y_inc = (end_y - ray_y) / steps;
    
    i = 0;
    while (i <= steps)
    {
        safe_put_pixel(win->mmap, (int)ray_x, (int)ray_y, RED);
        ray_x += x_inc;
        ray_y += y_inc;
        i++;
    }
}