/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sblanco- <sblanco-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:15:48 by sblanco-          #+#    #+#             */
/*   Updated: 2025/12/08 11:38:17 by sblanco-         ###   ########.fr       */
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
