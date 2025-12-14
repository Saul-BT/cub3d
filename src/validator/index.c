/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:15:48 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/08 18:40:14 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_map_valid(t_map map)
{
	if (!all_valid_chars(map.raw))
		return (false);
	if (!is_one_player(map.raw))
		return (false);
	if (!bfs(map))
		return (false);
	return (true);
}

bool	set_valid_textures(char **texture, t_win *win)
{
	win->wall_north = my_mlx_load_image(win, texture[NORTH]);
	if (!win->wall_north)
		return (false);
	win->wall_south = my_mlx_load_image(win, texture[SOUTH]);
	if (!win->wall_south)
		return (false);
	win->wall_east = my_mlx_load_image(win, texture[EAST]);
	if (!win->wall_east)
		return (false);
	win->wall_west = my_mlx_load_image(win, texture[WEST]);
	if (!win->wall_west)
		return (false);
	if (!set_valid_color(texture[C_FLOOR], &(win->floor_color))
		|| !set_valid_color(texture[C_CEILING], &(win->ceiling_color)))
		return (false);
	return (true);
}
