/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_motion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:21:41 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 13:07:36 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	move_player(t_cub *cub, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = cub->player->pos.x + dx;
	new_y = cub->player->pos.y + dy;
	if (new_x >= 0 && new_x <= cub->map_width)
		cub->player->pos.x = new_x;
	if (new_y >= 0 && new_y <= cub->map_height)
		cub->player->pos.y = new_y;
}

void	rotate_player(t_player *player, double rotation)
{
	double		old_dir_x;
	double		old_plane_x;
	double		dx;
	double		dy;

	dx = cos(rotation);
	dy = sin(rotation);
	old_dir_x = player->dir.x;
	player->dir.x = player->dir.x * dx - player->dir.y * dy;
	player->dir.y = old_dir_x * dy + player->dir.y * dx;
	old_plane_x = player->plane.x;
	player->plane.x = player->plane.x * dx - player->plane.y * dy;
	player->plane.y = old_plane_x * dy + player->plane.y * dx;
}

// MLX_KEY_W is already the standard movement, same direction
void	player_motion(t_player *player, keys_t key, t_cub *cub)
{
	double	dx;
	double	dy;

	dx = player->dir.x * MOVE_SPEED;
	dy = player->dir.y * MOVE_SPEED;
	if (key == MLX_KEY_S)
	{
		dx *= -1;
		dy *= -1;
	}
	else if (key == MLX_KEY_A)
		dy *= -1;
	else if (key == MLX_KEY_D)
		dx = -1;
	move_player(cub, dx, dy);
}
