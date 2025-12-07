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
static void	move_player(t_cub *cub, float dx, float dy)
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

void    player_motion(t_cub *cub, keys_t key)
{
    float	dx;
	float	dy;

    dx = 0;
	dy = 0;
    if (key == MLX_KEY_W)
    {
        dx = cos(cub->player->angle) * MOVE_SPEED;
        dy = sin(cub->player->angle) * MOVE_SPEED;
    }
    else if (key == MLX_KEY_S)
    {
        dx = -cos(cub->player->angle) * MOVE_SPEED;
        dy = -sin(cub->player->angle) * MOVE_SPEED;
    }
    else if (key == MLX_KEY_A)
    {
        dx = sin(cub->player->angle) * MOVE_SPEED;
        dy = -cos(cub->player->angle) * MOVE_SPEED;
    }
    else if (key == MLX_KEY_D)
    {
        dx = -sin(cub->player->angle) * MOVE_SPEED;
        dy = cos(cub->player->angle) * MOVE_SPEED;
    }
    move_player(cub, dx, dy);
}