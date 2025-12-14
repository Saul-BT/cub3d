/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 00:04:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 12:21:46 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(cub->win->mlx);
		exit(SUCCESS);
	}
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
	{
		if (keydata.key == MLX_KEY_W || keydata.key == MLX_KEY_A
			|| keydata.key == MLX_KEY_S || keydata.key == MLX_KEY_D)
			player_motion(cub->player, keydata.key, cub);
		else if (keydata.key == MLX_KEY_LEFT)
			rotate_player(cub->player, -ROTATION_SPEED);
		else if (keydata.key == MLX_KEY_RIGHT)
			rotate_player(cub->player, ROTATION_SPEED);
	}
	clear_screen(cub);
	draw_minimap(cub);
	raycast(cub);
}
