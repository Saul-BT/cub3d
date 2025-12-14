/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/14 13:01:20 by gade-oli          #+#    #+#             */
/*   Updated: 2025/12/14 13:08:00 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	is_player(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

static void	init_player_vals(t_player *player, int x, int y, char nsew)
{
	double	plane_length;

	plane_length = (double)WIN_WIDTH / ((double)WIN_HEIGHT * 2);
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	if (nsew == 'N')
	{
		player->dir = (t_dpoint){0, -1};
		player->plane = (t_dpoint){plane_length, 0};
	}
	else if (nsew == 'S')
	{
		player->dir = (t_dpoint){0, 1};
		player->plane = (t_dpoint){-plane_length, 0};
	}
	else if (nsew == 'E')
	{
		player->dir = (t_dpoint){1, 0};
		player->plane = (t_dpoint){0, plane_length};
	}
	else if (nsew == 'W')
	{
		player->dir = (t_dpoint){-1, 0};
		player->plane = (t_dpoint){0, -plane_length};
	}
}

void	init_player(t_player *player, char **map, int map_height)
{
	int		y;
	int		x;

	y = 0;
	while (y < map_height)
	{
		x = 0;
		while (map[y] && map[y][x])
		{
			if (is_player(map[y][x]))
			{
				init_player_vals(player, x, y, map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}
