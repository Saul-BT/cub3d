/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:21:41 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/13 12:44:19 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void init_player_dir(t_player *p, double dx, double dy, double px, double py)
{
	p->dir_x = dx;
	p->dir_y = dy;
	p->plane_x = px;
	p->plane_y = py;
}

void	init_player_position(t_player *player, char **map, int map_height)
{
	int	y;
	int	x;

	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (map[y] && map[y][x])
		{
			if (is_player(map[y][x]))
			{
				// Center of the tile
				player->x = x + 0.5;
				player->y = y + 0.5;
				if (map[y][x] == 'N')
					init_player_dir(player, 0, -1, FOV, 0);
				else if (map[y][x] == 'S')
					init_player_dir(player, 0, 1, -FOV, 0);
				else if (map[y][x] == 'E')
					init_player_dir(player, 1, 0, 0, FOV);
				else if (map[y][x] == 'W')
					init_player_dir(player, -1, 0, 0, -FOV);
				return ;
			}
			x++;
		}
		y++;
	}
}

//BONUS: remove bound checking for not breaking the map
static void	move_player(t_cub *cub, double dx, double dy)
{
	double new_x;
	double new_y;

	new_x = cub->player->x + dx;
	new_y = cub->player->y + dy;
    printf("Before move: x=%.2f, y=%.2f\n", cub->player->x, cub->player->y);
	if (new_x >= 0 && new_x <= cub->map_width)
		cub->player->x = new_x;
	if (new_y >= 0 && new_y <= cub->map_height)
		cub->player->y = new_y;
    printf("After move: x=%.2f, y=%.2f (dx=%.2f, dy=%.2f)\n", cub->player->x, cub->player->y, dx, dy);
}

void    rotate_player(t_player *p, double rotation)
{
    double		old_dir_x;
    double		old_plane_x;
    double		dx;
	double		dy;

	dx = cos(rotation);
	dy = sin(rotation);
	old_dir_x = p->dir_x;
    p->dir_x = p->dir_x * dx - p->dir_y * dy;
    p->dir_y = old_dir_x * dy + p->dir_y * dx;
    old_plane_x = p->plane_x;
    p->plane_x = p->plane_x * dx - p->plane_y * dy;
    p->plane_y = old_plane_x * dy + p->plane_y * dx;
}

void    player_motion(t_player *p, keys_t key, t_cub *cub)
{
    double	dx;
	double	dy;

    dx = 0;
	dy = 0;
    if (key == MLX_KEY_W)
    {
        dx = p->dir_x * MOVE_SPEED;
        dy = p->dir_y * MOVE_SPEED;
    }
    else if (key == MLX_KEY_S)
    {
        dx = -p->dir_x * MOVE_SPEED;
        dy = -p->dir_y * MOVE_SPEED;
    }
    else if (key == MLX_KEY_A)
    {
        dx = p->dir_y * MOVE_SPEED;
        dy = -p->dir_x * MOVE_SPEED;
    }
    else if (key == MLX_KEY_D)
    {
        dx = -p->dir_y * MOVE_SPEED;
        dy = p->dir_x * MOVE_SPEED;
    }
    move_player(cub, dx, dy);
}