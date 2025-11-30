/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 00:04:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/20 20:44:24 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;
	mlx_t	*mlx;
	float	dx;
	float	dy;

	cub = (t_cub *)param;
	mlx = cub->win->mlx;
	dx = 0;
	dy = 0;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		mlx_close_window(mlx);
	//TODO: separate player movement logic to another file
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
    {
        if (keydata.key == MLX_KEY_W)
        {
            dx = cos(cub->player->angle) * MOVE_SPEED;
            dy = sin(cub->player->angle) * MOVE_SPEED;
            move_player(cub, dx, dy);
        }
        else if (keydata.key == MLX_KEY_S)
        {
            dx = -cos(cub->player->angle) * MOVE_SPEED;
            dy = -sin(cub->player->angle) * MOVE_SPEED;
            move_player(cub, dx, dy);
        }
        else if (keydata.key == MLX_KEY_A)
        {
            dx = -sin(cub->player->angle) * MOVE_SPEED;
            dy = cos(cub->player->angle) * MOVE_SPEED;
            move_player(cub, dx, dy);
        }
        else if (keydata.key == MLX_KEY_D)
        {
            dx = sin(cub->player->angle) * MOVE_SPEED;
            dy = -cos(cub->player->angle) * MOVE_SPEED;
            move_player(cub, dx, dy);
        }
        else if (keydata.key == MLX_KEY_LEFT)
        {
            rotate_player(cub, -ROTATION_SPEED);
        }
        else if (keydata.key == MLX_KEY_RIGHT)
        {
            rotate_player(cub, ROTATION_SPEED);
        }
    }
}
