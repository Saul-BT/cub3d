/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:21:41 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 14:34:49 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	rotate_player(t_player *player, double rotation)
{
	double	old_dir_x;
	double	old_plane_x;
	double	dx;
	double	dy;

	dx = cos(rotation);
	dy = sin(rotation);
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * dx - player->dir.y * dy;
	player->dir.y = old_dir_x * dy + player->dir.y * dx;
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * dx - player->plane.y * dy;
	player->plane.y = old_plane_x * dy + player->plane.y * dx;
}

static int	is_wall(t_cub *cub, double x, double y)
{
	if (x < 0 || x >= cub->map.width || y < 0 || y >= cub->map.height)
		return (1);
	if (cub->map.raw[(int)y][(int)x] == '1')
		return (1);
	return (0);
}

static void	move_player(t_cub *cub, t_dpoint diff)
{
	t_dpoint	new_pos;

	new_pos.x = cub->player->pos.x + diff.x;
	new_pos.y = cub->player->pos.y + diff.y;
	if (!is_wall(cub, new_pos.x, cub->player->pos.y))
		cub->player->pos.x = new_pos.x;
	if (!is_wall(cub, cub->player->pos.x, new_pos.y))
		cub->player->pos.y = new_pos.y;
}

void	player_motion(t_player *player, keys_t key, t_cub *cub)
{
	t_dpoint	diff;

	if (key == MLX_KEY_W)
	{
		diff.x = player->dir.x * MOVE_SPEED;
		diff.y = player->dir.y * MOVE_SPEED;
	}
	if (key == MLX_KEY_S)
	{
		diff.x = -player->dir.x * MOVE_SPEED;
		diff.y = -player->dir.y * MOVE_SPEED;
	}
	if (key == MLX_KEY_A)
	{
		diff.x = player->dir.y * MOVE_SPEED;
		diff.y = -player->dir.x * MOVE_SPEED;
	}
	if (key == MLX_KEY_D)
	{
		diff.x = -player->dir.y * MOVE_SPEED;
		diff.y = player->dir.x * MOVE_SPEED;
	}
	move_player(cub, diff);
}
