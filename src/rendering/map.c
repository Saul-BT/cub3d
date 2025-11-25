/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gade-oli <gade-oli@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 20:46:13 by gade-oli          #+#    #+#             */
/*   Updated: 2025/11/24 20:46:39 by gade-oli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

//atm for 2D minimap
void	get_map_dimensions(char **map, t_cub *cub)
{
	int	y;
	int	x;
	int	max_x;

	if (!map)
		return ;
	max_x = 0;
	x = 0;
	y = 0;
	while (cub->map[y])
	{
		x = ft_strlen(map[y]);
		if (x > max_x)
			max_x = x;
		y++;
	}
	cub->map_height = y;
	cub->map_width = max_x;
}