/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/30 20:42:04 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/30 20:42:06 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../inc/cub3d.h"

int is_ray_touching_wall(t_cub *cub, float px, float py)
{
	int	x;
	int	y;

	x = px / TILE;
	y = py / TILE;
	if (cub->map[y][x] == '1')
		return (1);
	return (0);
}

void dda(t_cub *cub, t_player *player)
{

}