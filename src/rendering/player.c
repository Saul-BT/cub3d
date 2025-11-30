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

void	init_player_position(t_cub *cub)
{
    int	i;
    int	j;

    j = 0;
    cub->player->angle = 0.0;
	cub->player->x = 0.0;
	cub->player->y = 0.0;
    while (j < cub->map_height)
    {
        i = 0;
        while (cub->map[j] && cub->map[j][i])
        {
            if (is_player(cub->map[j][i]))
            {
                cub->player->x = i;
                cub->player->y = j;
                return ;
            }
            i++;
        }
        j++;
    }
}

//only used for the minimap atm

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