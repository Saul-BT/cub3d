/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   index.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:15:48 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/15 20:14:15 by sblanco-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

bool	is_map_valid(t_map map)
{
	if (!all_valid_chars(map.raw))
		return (ft_error("forbbiden characters in map."), false);
	if (!is_one_player(map.raw))
		return (ft_error("should have 1 player."), false);
	if (!bfs(map))
		return (ft_error("malformed/unclosed map."), false);
	return (true);
}

bool	set_valid_textures(char **texture, t_win *win)
{
	win->wall_north = mlx_load_png(texture[NORTH]);
	if (!win->wall_north)
		return (false);
	win->wall_south = mlx_load_png(texture[SOUTH]);
	if (!win->wall_south)
		return (false);
	win->wall_east = mlx_load_png(texture[EAST]);
	if (!win->wall_east)
		return (false);
	win->wall_west = mlx_load_png(texture[WEST]);
	if (!win->wall_west)
		return (false);
	if (!set_valid_color(texture[C_FLOOR], &(win->floor_color))
		|| !set_valid_color(texture[C_CEILING], &(win->ceiling_color)))
		return (false);
	return (true);
}
